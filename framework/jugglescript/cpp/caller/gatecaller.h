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

class gate: public Fossilizid::juggle::caller{
public:
	gate(boost::shared_ptr<Fossilizid::juggle::process> __process, boost::shared_ptr<Fossilizid::juggle::channel> ch) : caller(__process, ch, "gate"){
	}

	~gate(){
	}

	void register_logic(std::string ip,int64_t port){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = call_module_method_sync("gate_register_logic", v);
		return ;
	}

};

}

namespace async{

class gate: public Fossilizid::juggle::caller{
public:
	gate(boost::shared_ptr<Fossilizid::juggle::process> __process, boost::shared_ptr<Fossilizid::juggle::channel> ch) : caller(__process, ch, "gate"){
	}

	~gate(){
	}

	void register_logic(std::string ip, int64_t port, boost::function<void(void)> callback){
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*v)["ip"] = ip;
		(*v)["port"] = port;
		auto cb = [this, callback](boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r){
		};
		call_module_method_async("gate_register_logic", v, cb);
	}

};

}

