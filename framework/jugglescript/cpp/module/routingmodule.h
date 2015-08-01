/*
 * juggle codegen code explain notes
 *
 * juggle is a rpc framework under the GPL v2 License
 * 
 * juggle codegen generate rcp code
 * only for send message and dispense message
 * so users need write code handle process message
 *
 * this notes create in 2015.4.26
 * made for juggle codegen
 * autor qianqians
 */

/*
 * juggle codegen code explain notes
 *
 * juggle is a rpc framework under the GPL v2 License
 * 
 * juggle codegen generate rcp code
 * only for send message and dispense message
 * so users need write code handle process message
 *
 * this notes create in 2015.4.26
 * made for juggle codegen
 * autor qianqians
 */

#include <juggle.h>
#include <boost/make_shared.hpp>
#include <string>

namespace module{

class routing: public Fossilizid::juggle::module{
public:
	routing(boost::shared_ptr<Fossilizid::juggle::process> __process) : module(__process, "routing", Fossilizid::uuid::UUID()){
		_module_func.push_back("routing_register_logic");
		_module_func.push_back("routing_register_gate");
		_module_func.push_back("routing_register_user");
		_module_func.push_back("routing_unregister_user");
		_module_func.push_back("routing_get_user");
		__process->register_module_method("routing_register_logic", boost::bind(&routing::call_register_logic, this, _1, _2));
		__process->register_module_method("routing_register_gate", boost::bind(&routing::call_register_gate, this, _1, _2));
		__process->register_module_method("routing_register_user", boost::bind(&routing::call_register_user, this, _1, _2));
		__process->register_module_method("routing_unregister_user", boost::bind(&routing::call_unregister_user, this, _1, _2));
		__process->register_module_method("routing_get_user", boost::bind(&routing::call_get_user, this, _1, _2));
	}

	~routing(){
	}

	boost::signals2::signal< void(int64_t logicnum,std::string ip,int64_t port)> sigregister_logic;

	void call_register_logic(boost::shared_ptr<Fossilizid::juggle::channel> ch, boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v){
		auto logicnum = boost::any_cast<int64_t>((*v)["logicnum"]);
		auto ip = boost::any_cast<std::string>((*v)["ip"]);
		auto port = boost::any_cast<int64_t>((*v)["port"]);
		sigregister_logic(logicnum, ip, port);
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*r)["suuid"] = boost::any_cast<std::string>((*v)["suuid"]);
		(*r)["method"] = boost::any_cast<std::string>((*v)["method"]);
		(*r)["rpcevent"] = "reply_rpc_method";

		ch->push(r);
	}

	boost::signals2::signal< void(int64_t gatenum,std::string ip,int64_t port)> sigregister_gate;

	void call_register_gate(boost::shared_ptr<Fossilizid::juggle::channel> ch, boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v){
		auto gatenum = boost::any_cast<int64_t>((*v)["gatenum"]);
		auto ip = boost::any_cast<std::string>((*v)["ip"]);
		auto port = boost::any_cast<int64_t>((*v)["port"]);
		sigregister_gate(gatenum, ip, port);
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*r)["suuid"] = boost::any_cast<std::string>((*v)["suuid"]);
		(*r)["method"] = boost::any_cast<std::string>((*v)["method"]);
		(*r)["rpcevent"] = "reply_rpc_method";

		ch->push(r);
	}

	boost::signals2::signal< void(std::string uuid,std::string ip,int64_t port)> sigregister_user;

	void call_register_user(boost::shared_ptr<Fossilizid::juggle::channel> ch, boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v){
		auto uuid = boost::any_cast<std::string>((*v)["uuid"]);
		auto ip = boost::any_cast<std::string>((*v)["ip"]);
		auto port = boost::any_cast<int64_t>((*v)["port"]);
		sigregister_user(uuid, ip, port);
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*r)["suuid"] = boost::any_cast<std::string>((*v)["suuid"]);
		(*r)["method"] = boost::any_cast<std::string>((*v)["method"]);
		(*r)["rpcevent"] = "reply_rpc_method";

		ch->push(r);
	}

	boost::signals2::signal< void(std::string uuid)> sigunregister_user;

	void call_unregister_user(boost::shared_ptr<Fossilizid::juggle::channel> ch, boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v){
		auto uuid = boost::any_cast<std::string>((*v)["uuid"]);
		sigunregister_user(uuid);
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*r)["suuid"] = boost::any_cast<std::string>((*v)["suuid"]);
		(*r)["method"] = boost::any_cast<std::string>((*v)["method"]);
		(*r)["rpcevent"] = "reply_rpc_method";

		ch->push(r);
	}

	boost::signals2::signal< int64_t(std::string uuid)> sigget_user;

	void call_get_user(boost::shared_ptr<Fossilizid::juggle::channel> ch, boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v){
		auto uuid = boost::any_cast<std::string>((*v)["uuid"]);
		auto ret = sigget_user(uuid);
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*r)["suuid"] = boost::any_cast<std::string>((*v)["suuid"]);
		(*r)["method"] = boost::any_cast<std::string>((*v)["method"]);
		(*r)["rpcevent"] = "reply_rpc_method";

		(*r)["ret"] = ret;
		ch->push(r);
	}

};

}
