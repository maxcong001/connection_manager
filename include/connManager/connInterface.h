#pragma once
#include "connManager/util.h"
#include "connManager/connManager.h"

template <typename connInfo>
class RedisConn : public std::enable_shared_from_this<RedisConn<connInfo>>
{
  public:
    typedef connInfo conn_type_t;
    RedisConn() = delete;
    RedisConn(connInfo info)
    {
        _info = info;
        __LOG(debug, "new Redis connection! " << (void *)this);
    }
    void onConnected()
    {
        __LOG(debug, "enter. connection id is : " << get_conn_inc_id()<<" pool index is : "<< get_pool_index());
        set_conn_state(true);
        // tell pool that there is a new connection
        auto bus = message_bus<connPool<RedisConn<connInfo>>>::instance();
        bus->call(CONN_INC, this, get_conn_inc_id());
    }
    void onDisconnected(int error)
    {
        __LOG(debug, "enter. connection id is : " << get_conn_inc_id()<<" pool index is : "<< get_pool_index());
        set_conn_state(false);
        // tell pool that a connection is deleted
        auto bus = message_bus<connPool<RedisConn<connInfo>>>::instance();
        bus->call(CONN_DEC, this, get_conn_dec_id());
    }

    bool connect(connInfo info)
    {
        RedisConn<connInfo>::onConnected();
        return true;
    }

    bool disconnect() { return true; }

    connInfo get_conn_info() { return _info; }
    void set_pool_index(int index) { pool_index = index; }
    int get_pool_index() { return pool_index; }
    bool get_conn_state() { return conn_state; }
    void set_conn_state(bool stat) { conn_state = stat; }
    void set_conn_inc_id(int id) { conn_inc_id = id; }
    void set_conn_dec_id(int id) { conn_dec_id = id; }
    int get_conn_inc_id() { return conn_inc_id; }
    int get_conn_dec_id() { return conn_dec_id; }
    connInfo _info;
    int pool_index;
    bool conn_state;

    int conn_inc_id;
    int conn_dec_id;
};
