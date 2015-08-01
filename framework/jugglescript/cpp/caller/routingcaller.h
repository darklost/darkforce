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

namespace sync{

class routing: public Fossilizid::juggle::caller{
public:
	routing(boost::shared_ptr<Fossilizid::juggle::process> __process, boost::shared_ptr<Fossilizid::juggle::channel> ch) : caller(__process, ch, "routing"){
	}

	~routing(){
	}

	void register_logic(int64_t logicnum,std::string ip,int64_t port){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["logicnum"] = logicnum;
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = call_module_method_sync("routing_register_logic", v);
		return ;
	}

	void register_gate(int64_t gatenum,std::string ip,int64_t port){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["gatenum"] = gatenum;
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = call_module_method_sync("routing_register_gate", v);
		return ;
	}

	void register_user(std::string uuid,std::string ip,int64_t port){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["uuid"] = uuid;
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = call_module_method_sync("routing_register_user", v);
		return ;
	}

	void unregister_user(std::string uuid){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["uuid"] = uuid;
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = call_module_method_sync("routing_unregister_user", v);
		return ;
	}

	int64_t get_user(std::string uuid){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["uuid"] = uuid;
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = call_module_method_sync("routing_get_user", v);
		return boost::any_cast<int64_t>((*r)["ret"]);;
	}

};

}

namespace async{

class routing: public Fossilizid::juggle::caller{
public:
	routing(boost::shared_ptr<Fossilizid::juggle::process> __process, boost::shared_ptr<Fossilizid::juggle::channel> ch) : caller(__process, ch, "routing"){
	}

	~routing(){
	}

	void register_logic(int64_t logicnum, std::string ip, int64_t port, boost::function<void(void)> callback){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["logicnum"] = logicnum;
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		auto cb = [this, callback](boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r){
		};
		call_module_method_async("routing_register_logic", v, cb);
	}

	void register_gate(int64_t gatenum, std::string ip, int64_t port, boost::function<void(void)> callback){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["gatenum"] = gatenum;
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		auto cb = [this, callback](boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r){
		};
		call_module_method_async("routing_register_gate", v, cb);
	}

	void register_user(std::string uuid, std::string ip, int64_t port, boost::function<void(void)> callback){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["uuid"] = uuid;
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		auto cb = [this, callback](boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r){
		};
		call_module_method_async("routing_register_user", v, cb);
	}

	void unregister_user(std::string uuid, boost::function<void(void)> callback){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["uuid"] = uuid;
		auto cb = [this, callback](boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r){
		};
		call_module_method_async("routing_unregister_user", v, cb);
	}

	int64_t get_user(std::string uuid, boost::function<void(int64_t)> callback){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["uuid"] = uuid;
		auto cb = [this, callback](boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r){
			int64_t ret = boost::any_cast<int64_t>((*r)["ret"]);
			callback(ret);
        };
		call_module_method_async("routing_get_user", v, cb);
	}

};

}

