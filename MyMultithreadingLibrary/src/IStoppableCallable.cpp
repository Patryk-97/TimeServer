#include "IStoppableCallable.h"

IStoppableCallable::IStoppableCallable()
{

}

IStoppableCallable::~IStoppableCallable()
{

}

void IStoppableCallable::operator()(void)
{
   this->run();
}

void IStoppableCallable::stop(void)
{
   this->isStoppedFlag = true;
}

bool IStoppableCallable::isStopped(void)
{
   return this->isStoppedFlag.load();
}