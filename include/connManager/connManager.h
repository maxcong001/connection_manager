#pragma once
#include "connManager/util.h"
#include "connManager/connPool.h"
template <typename DBConn, typename connInfo>
class connManager
{
  public:
    using pool_ptr_t = std::shared_ptr<connPool<DBConn, connInfo>>;

    int add_pool()
    {
        pool_ptr_t pool(new connPool<DBConn, connInfo>());
        for (auto p_info : infoList)
        {
            pool->add_conn(p_info);
        }
        int id = getUniqueID();
        pool->set_id(id);
        poolList.emplace_back(pool);
        return id;
    }
    bool del_pool(int id)
    {
        poolList.remove_if([&](const pool_ptr_t &ptr_t) -> bool {
            if (ptr_t->get_id() == id)
            {
                return true;
            }
            else
            {
                return false;
            }
        });
        return true;
    }
    pool_ptr_t get_pool()
    {
        auto tmp = poolList.front();
        poolList.pop_front();
        poolList.push_back(tmp);
        return tmp;
    }

    //typename connPool<DBConn, connInfo>::DBConn_ptr_t

    auto get_conn() -> typename connPool<DBConn, connInfo>::DBConn_ptr_t
    {
        return get_pool()->get_conn();
    }

    bool add_conn(connInfo info)
    {
        infoList.emplace_back(info);
        for (auto tmp : poolList)
        {
            tmp->add_conn(info);
        }
        return true;
    }
    bool del_conn(connInfo info)
    {
        infoList.erase(info);
        for (auto tmp : poolList)
        {
            tmp->del_conn(info);
        }
        return true;
    }

  private:
    int getUniqueID()
    {
        return (uniqueID_atomic++);
    }
    std::atomic<int> uniqueID_atomic;
    std::list<connInfo> infoList; // just used when add a new pool.
    std::list<pool_ptr_t> poolList;
};