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

class gate: public Fossilizid::juggle::module{
public:
	gate(boost::shared_ptr<Fossilizid::juggle::process> __process) : module(__process, "gate", Fossilizid::uuid::UUID()){
		_module_func.push_back("gate_register_logic");
		__process->register_module_method("gate_register_logic", boost::bind(&gate::call_register_logic, this, _1, _2));
	}

	~gate(){
	}

	boost::signals2::signal< void(std::string ip,int64_t port)> sigregister_logic;

	void call_register_logic(boost::shared_ptr<Fossilizid::juggle::channel> ch, boost::shared_ptr<boost::unordered_map<std::string, boost::any> > v){
		auto ip = boost::any_cast<std::string>((*v)["ip"]);
		auto port = boost::any_cast<int64_t>((*v)["port"]);
		sigregister_logic(ip, port);
		boost::shared_ptr<boost::unordered_map<std::string, boost::any> > r = boost::make_shared<boost::unordered_map<std::string, boost::any> >();
		(*r)["suuid"] = boost::any_cast<std::string>((*v)["suuid"]);
		(*r)["method"] = boost::any_cast<std::string>((*v)["method"]);
		(*r)["rpcevent"] = "reply_rpc_method";

		ch->push(r);
	}

};

}
