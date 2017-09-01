#include <async/scheduler.h>
#include <mutex>

using namespace IOService;
using namespace std;


std::unique_ptr<Scheduler> Scheduler::_instance;


Scheduler & Scheduler::instance()
{
    static once_flag flag;
    call_once(flag, [] { _instance.reset(new Scheduler); } );
    return *_instance;
}


void Scheduler::destroy()
{
    stop();
    _instance.reset();
}

Scheduler::Scheduler()
{
}
