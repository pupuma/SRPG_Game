#include "Game.h"


#include "PathfindingImmedateState.h"
#include "Character.h"


PathfindingImmedateState::PathfindingImmedateState(Character* _character)
	: PathfindingState(_character)
{
}


PathfindingImmedateState::~PathfindingImmedateState()
{
}

void PathfindingImmedateState::Start()
{
	PathfindingState::Start();

	while (0 != pathfindingQueue.size())
	{
		if (eUpdateState::BUILD_PATH == updateState)
		{
			break;
		}
		UpdatePathfinding();
	}

	while (eStateType::ST_PATH_MOVE != nextState)
	{
		UpdateBuildPath();
	}
}
