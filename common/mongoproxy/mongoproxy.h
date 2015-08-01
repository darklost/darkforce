/*
 * mongoproxy.h
 *
 *  Created on: 2015-3-31
 *      Author: qianqians
 */
#ifndef _mongoproxy_h
#define _mongoproxy_h

#include <mongoc.h>

#include <string>
#include <unordered_map>

#include "../config/config.h"

namespace Fossilizid{
namespace mongoproxy{

class dbproxy{
public:
	dbproxy(boost::shared_ptr<config::config> _config);
	~dbproxy();

public:
	bool create_index(std::string collection_name, const bson_t * keys, const mongoc_index_opt_t *opt, bson_error_t * error);
	
	bool drop_index (std::string collection, const std::string index_name, bson_error_t * error);

	mongoc_cursor_t * find_indexes (std::string  collection, bson_error_t * error);

	int64_t count(std::string collection_name, mongoc_query_flags_t flags, const bson_t * query, int64_t skip, int64_t limit, const mongoc_read_prefs_t * read_prefs, bson_error_t * error);
	
	bool insert(std::string collection, mongoc_insert_flags_t flags, const bson_t * document, const mongoc_write_concern_t * write_concern, bson_error_t * error);
	
	bool save(std::string collection, const bson_t * document, const mongoc_write_concern_t * write_concern, bson_error_t * error);
	
	bool update (std::string collection, mongoc_update_flags_t flags, const bson_t * selector, const bson_t * update, const mongoc_write_concern_t * write_concern, bson_error_t * error);

	bool remove(std::string collection, mongoc_remove_flags_t flags, const bson_t * selector, const mongoc_write_concern_t * write_concern, bson_error_t * error);

	mongoc_cursor_t * find(std::string collection, mongoc_query_flags_t flags, uint32_t skip, uint32_t limit, uint32_t batch_size, const bson_t * query, const bson_t * fields, const mongoc_read_prefs_t * read_prefs);
	
	bool find_and_modify(std::string collection, const bson_t * query, const bson_t * sort, const bson_t * update, const bson_t * fields, bool _remove, bool upsert, bool _new, bson_t * reply, bson_error_t * error);

	bool validate(std::string collection, const bson_t * options, bson_t * reply, bson_error_t * error);
	
	bool stats(std::string collection, const bson_t *options, bson_t *reply, bson_error_t *error);

private:
	mongoc_collection_t * get_collection(std::string collection_name);

private:
	mongoc_client_t * _client;
	mongoc_database_t * _db;
	std::unordered_map<std::string, mongoc_collection_t *> collectiondict;

};

} /* namespace mongoproxy */
} /* namespace Fossilizid */

#endif //_log_h