#pragma once
#include "connManager/util.h"
template <typename DBConn>
class connPool
{
  public:
    using connInfo = typename DBConn::conn_type_t;
    using DBConn_ptr_t = std::shared_ptr<DBConn>;

    bool add_conn(connInfo info)
    {
        DBConn_ptr_t DBIns(new DBConn(info));
        if (!info.type)
        {
            DBInsLocalList.emplace_back(DBIns);
        }
        else
        {
            DBInsRemoteList.emplace_back(DBIns);
        }
        return true;
    }
    bool del_conn(connInfo info)
    {
        if (!info.type)
        {
            DBInsLocalList.remove_if([&](const DBConn_ptr_t &db) -> bool {
                if (db->get_conn_info() == info)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            });
        }
        else
        {
            DBInsRemoteList.remove_if([&](const DBConn_ptr_t &db) -> bool {
                if (db->get_conn_info() == info)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            });
        }
        return true;
    }

    DBConn_ptr_t get_conn()
    {
        if (DBInsLocalList.size())
        {
            auto tmp = DBInsLocalList.front();
            DBInsLocalList.pop_front();
            DBInsLocalList.push_back(tmp);
            return tmp;
        }
        else
        {
            auto tmp = DBInsRemoteList.front();
            DBInsRemoteList.pop_front();
            DBInsRemoteList.push_back(tmp);
            return tmp;
        }
    }
    void set_id(int id)
    {
        _id = id;
    }
    int get_id()
    {
        return _id;
    }

  private:
    int _id;

    std::list<DBConn_ptr_t> DBInsLocalList;
    std::list<DBConn_ptr_t> DBInsRemoteList;
};