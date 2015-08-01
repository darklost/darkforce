/*
 * gate.cpp
 *
 *  Created on: 2015-1-17
 *      Author: qianqians
 */
#include "gate.h"

#include <config/config.h>

namespace Fossilizid{
namespace gate{
	
gate::gate(std::string filename, std::string key){
	isrun = true;

	boost::shared_ptr<config::config> _config = boost::make_shared<config::config>(filename);

	auto center_config = _config->get_value_dict("center");
	if (center_config == 0){
		throw std::exception("cannot find center config");
	} else{
		try{
			center_addr.first = center_config->get_value_string("ip");
			center_addr.second = (short)center_config->get_value_int("port");
		} catch(...){
			throw std::exception("center config field error");
		}
	}

	auto routing_config = _config->get_value_dict("routing");
	if (routing_config == 0){
		throw std::exception("cannot find routing config");
	} else{
		try{
			auto size = routing_config->get_list_size();
			routing_server.resize(size);
			for (uint32_t i = 0; i < size; i++){
				auto cfig = routing_config->get_list_dict(i);
				routing_server[cfig->get_value_int("serial ")].first.first = cfig->get_value_string("ip");
				routing_server[cfig->get_value_int("serial ")].first.second = cfig->get_value_int("port");
				routing_server[cfig->get_value_int("serial ")].second = nullptr;
			}
		} catch (...){
			throw std::exception("routing config field error");
		}
	}

	_service = juggle::create_service();
	
	_channelservice = boost::make_shared<achieve::channelservice>();
	_rpcproxy = boost::make_shared<rpcproxy>(boost::bind(&gate::get_channel, this, _1, _2));
	_usersessioncontainer = boost::make_shared<achieve::sessioncontainer>(_channelservice, _rpcproxy);
	
	_usersessioncontainer->sigdisconn.connect(boost::bind(&gate::user_disconn, this, _1));

	auto gate_config = _config->get_value_dict("key");
	if (gate_config == 0){
		throw std::exception("cannot find this config");
	} else{
		_blackacceptor = boost::make_shared<acceptor::blackacceptor>(gate_config, _channelservice, _usersessioncontainer);
	}

	_timerservice = timer::timerservice::createinstance();

	_process = boost::make_shared<juggle::process>();

	_module = boost::make_shared<module::gate>(_process);
	_module->sigregister_logic.connect(boost::bind(&gate::add_logic, this, _1, _2));

	_logicsessioncontainer = boost::make_shared<achieve::sessioncontainer>(_channelservice, _process);
	_logicconnector = boost::make_shared<connector::connector>(_channelservice, _logicsessioncontainer);

	_routingsessioncontainer = boost::make_shared<achieve::sessioncontainer>(_channelservice, _process);
	_routingconnector = boost::make_shared<connector::connector>(_channelservice, _routingsessioncontainer);

	_centersessioncontainer = boost::make_shared<achieve::sessioncontainer>(_channelservice, _process);
	_centerconnector = boost::make_shared<connector::connector>(_channelservice, _centersessioncontainer);
}

gate::~gate(){
}

void gate::user_disconn(boost::shared_ptr<juggle::channel> ch){
	auto it = ch_map.find(ch);
	auto lgc = logic_map.find(it->second.first);
	lgc->second.get<2>()->unregister_user(it->second.second);
}

void gate::run(){
	_service->init();

	while (isrun.load()){
		{
			for (uint32_t i = 0; i < routing_server.size(); i++){
				auto addr = routing_server[i];
				if (addr.second.get() == nullptr){
					boost::shared_ptr<juggle::channel> ch = _logicconnector->connect(addr.first.first.c_str(), addr.first.second);
					if (ch != 0){
						addr.second = ch;
						auto c = boost::make_shared<sync::logic>(_process, ch);
						routing_map.insert(std::make_pair(ch, boost::make_tuple(addr.first.first, addr.first.second, i)));
					}
				}
			}

			for (auto it = logic_server.begin(); it != logic_server.end(); ){
				boost::shared_ptr<juggle::channel> ch = _logicconnector->connect(it->first.c_str(), it->second);
				if (ch != 0){
					auto c = boost::make_shared<sync::logic>(_process, ch);
					logic_map.insert(std::make_pair(ch, boost::make_tuple(it->first, it->second, c)));
					it = logic_server.erase(it);
				} else {
					it++;
				}
			}
		}

		_channelservice->poll(_timerservice->get_event_time());

		_service->poll();

		_timerservice->poll(_service->unixtime());
	}
}

void gate::cancle_gate(){
	isrun.store(false);
}

void gate::add_logic(std::string ip, short port){
	boost::shared_ptr<juggle::channel> ch = _logicconnector->connect(ip.c_str(), port);
	if (ch != 0){
		auto c = boost::make_shared<sync::logic>(_process, ch);
		logic_map.insert(std::make_pair(ch, boost::make_tuple(ip, port, c)));
	} else{
		logic_server.push_back(std::make_pair(ip, port));
	}
}

boost::shared_ptr<juggle::channel> gate::get_channel(boost::shared_ptr<juggle::channel> ch, uuid::uuid user){
	for (auto i : logic_map){
		if (i.second.get<2>()->register_user(user)){
			auto logic_ch = i.first;
			ch_map.insert(std::make_pair(ch, std::make_pair(logic_ch, user)));
			return logic_ch;
		}
	}
	return nullptr;
}

} /* namespace routing */
} /* namespace Fossilizid */

