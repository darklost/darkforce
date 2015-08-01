/*
 * acceptor.cpp
 *
 *  Created on: 2015-1-17
 *      Author: qianqians
 */
#include "channelservice.h"

#include "../acceptor/blackacceptor.h"
#include "../acceptor/writeacceptor.h"

#include <boost/make_shared.hpp>

namespace Fossilizid{
namespace acceptor{

blackacceptor::blackacceptor(boost::shared_ptr<config::config> _config, boost::shared_ptr<achieve::channelservice> _chservice, boost::shared_ptr<achieve::sessioncontainer> _sc){
	acp = boost::make_shared<achieve::acceptor>(_chservice, _sc);
	
	auto ip = _config->get_value_string("ip");
	auto port = (short)_config->get_value_int("port");

	acp->init((char*)ip.c_str(), port);

	auto set = boost::make_shared<std::vector<std::pair<std::string, short> > >();
	auto dict = _config->get_value_dict("blacklist");
	for (size_t i = 0; i < dict->get_list_size(); i++){
		auto e = dict->get_list_dict(i);
		auto ip = e->get_list_string(0);
		auto port = (short)e->get_list_int(1);
		set->push_back(std::make_pair(ip, port));
	}
	
	epfitle = boost::make_shared<fitle::fitle<std::pair<std::string, short> > >();

	epfitle->setfitle(
		[set](std::pair<std::string, short> ep){
			for(auto e : *set){
				if (ep.first == e.first){
					if (e.second == 0){
						return true;
					}else if (e.second == ep.second){
						return true;
					}
				}
			}
			return false;
		}
	);

	acp->set_fitle(epfitle);
}

blackacceptor::~blackacceptor(){
}

writeacceptor::writeacceptor(boost::shared_ptr<config::config> _config, boost::shared_ptr<achieve::channelservice> _chservice, boost::shared_ptr<achieve::sessioncontainer> _sc){
	acp = boost::make_shared<achieve::acceptor>(_chservice, _sc);
	
	auto ip = _config->get_value_string("ip");
	auto port = (short)_config->get_value_int("port");
	
	acp->init((char*)ip.c_str(), port);

	auto set = boost::make_shared<std::vector<std::pair<std::string, short> > >();
	auto dict = _config->get_value_dict("writelist");
	for (size_t i = 0; i < dict->get_list_size(); i++){
		auto e = dict->get_list_dict(i);
		auto ip = e->get_list_string(0);
		auto port = (short)e->get_list_int(1);
		set->push_back(std::make_pair(ip, port));
	}

	epfitle = boost::make_shared<fitle::fitle<std::pair<std::string, short> > >();

	epfitle->setfitle(
		[set](std::pair<std::string, short> ep){
			for(auto e : *set){
				if (ep.first == e.first){
					if (e.second == 0){
						return false;
					}else if (e.second == ep.second){
						return false;
					}
				}else{
					return false;
				}
			}
			return true;
		}
	);

	acp->set_fitle(epfitle);
}

writeacceptor::~writeacceptor(){
}


} /* namespace acceptor */
} /* namespace Fossilizid */

