#include "LeafTask.h"



LeafTask::LeafTask():Task()
{
}

LeafTask::LeafTask(BehaviorTree * tree, Task * control) : Task(tree, control)
{
}


LeafTask::~LeafTask()
{
}
