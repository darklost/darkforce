/*
 * mongoproxy.cpp
 *
 *  Created on: 2015-3-31
 *      Author: qianqians
 */
#include "mongoproxy.h"

namespace Fossilizid{
namespace mongoproxy{

dbproxy::dbproxy(boost::shared_ptr<config::config> _config){
	mongoc_init();
	
	mongoc_uri_t * _uri = mongoc_uri_new_for_host_port(_config->get_value_string("ip").c_str(), _config->get_value_int("port"));
	_client = mongoc_client_new(mongoc_uri_get_string(_uri));
	mongoc_uri_destroy(_uri);

	_db = mongoc_client_get_database(_client, _config->get_value_string("db").c_str());
}

dbproxy::~dbproxy(){
	for(auto it : collectiondict){
		mongoc_collection_destroy(it.second);
	}
	mongoc_database_destroy(_db);
	mongoc_client_destroy(_client);
	mongoc_cleanup();
}

mongoc_collection_t * dbproxy::get_collection(std::string collection_name){
	auto it = collectiondict.find(collection_name);
	if (it != collectiondict.end()){
		return it->second;
	}

	return mongoc_database_get_collection(_db, collection_name.c_str());
}


bool dbproxy::create_index(std::string collection_name, const bson_t * keys, const mongoc_index_opt_t *opt, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection_name);
	return mongoc_collection_create_index(_c, keys, opt, error);
}
	
bool dbproxy::drop_index (std::string collection, const std::string index_name, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_drop_index(_c, index_name.c_str(), error);
}

mongoc_cursor_t * dbproxy::find_indexes(std::string  collection, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_find_indexes(_c, error);
}

int64_t dbproxy::count(std::string collection_name, mongoc_query_flags_t flags, const bson_t * query, int64_t skip, int64_t limit, const mongoc_read_prefs_t * read_prefs, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection_name);
	return mongoc_collection_count(_c, flags, query, skip, limit, read_prefs, error);
}
	
bool dbproxy::insert(std::string collection, mongoc_insert_flags_t flags, const bson_t * document, const mongoc_write_concern_t * write_concern, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_insert(_c, flags, document, write_concern, error);
}
	
bool dbproxy::save(std::string collection, const bson_t * document, const mongoc_write_concern_t * write_concern, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_save(_c, document, write_concern, error);
}
	
bool dbproxy::update (std::string collection, mongoc_update_flags_t flags, const bson_t * selector, const bson_t * update, const mongoc_write_concern_t * write_concern, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_update(_c, flags, selector, update, write_concern, error);
}

bool dbproxy::remove(std::string collection, mongoc_remove_flags_t flags, const bson_t * selector, const mongoc_write_concern_t * write_concern, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_remove(_c, flags, selector, write_concern, error);
}

mongoc_cursor_t * dbproxy::find(std::string collection, mongoc_query_flags_t flags, uint32_t skip, uint32_t limit, uint32_t batch_size, const bson_t * query, const bson_t * fields, const mongoc_read_prefs_t * read_prefs){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_find(_c, flags, skip, limit, batch_size, query, fields, read_prefs);
}
	
bool dbproxy::find_and_modify(std::string collection, const bson_t * query, const bson_t * sort, const bson_t * update, const bson_t * fields, bool _remove, bool upsert, bool _new, bson_t * reply, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_find_and_modify(_c, query, sort, update, fields, _remove, upsert, _new, reply, error);
}

bool dbproxy::validate(std::string collection, const bson_t * options, bson_t * reply, bson_error_t * error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_validate(_c, options, reply, error);
}
	
bool dbproxy::stats(std::string collection, const bson_t *options, bson_t *reply, bson_error_t *error){
	mongoc_collection_t * _c = get_collection(collection);
	return mongoc_collection_stats(_c, options, reply, error);
}


} /* namespace mongoproxy */
} /* namespace Fossilizid */

