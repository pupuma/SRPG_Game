#include "Game.h"
#include "ParsingSystem.h"



ParsingSystem::ParsingSystem()
{
}


ParsingSystem::~ParsingSystem()
{
}

void ParsingSystem::MapDataParsing(std::string _fileName)
{
	while (!q_TileMapLayerBase.empty())
	{
		q_TileMapLayerBase.pop();
	}

	while (!q_TileMapLayerTile.empty())
	{
		q_TileMapLayerTile.pop();
	}

	while (!q_TileMapLayerObject.empty())
	{
		q_TileMapLayerObject.pop();
	}


	std::vector<std::string> recordList = RESOURCEMANAGER->FindScript(_fileName);

	TCHAR record[1000];
	TCHAR* token;
	
	strcpy_s(record, recordList[0].c_str());
	token = strtok(record, ",");		
	token = strtok(NULL, ",");			
	tileWidth = atoi(token);
	token = strtok(NULL, ",");			
	tileHeight = atoi(token);

	memset(record, 0, sizeof(TCHAR) * 256);

	strcpy_s(record, recordList[1].c_str());
	token = strtok(record, ",");		
	token = strtok(NULL, ",");			
	layerSize = atoi(token);


	int iLine = 2;

	bool isParsing = true;
	std::string strRecord;

	int iCount = 0;
	while (iLine != recordList.size()-1)
	{
		if (recordList[iLine].substr(0, 5) == "Layer")
		{
			iLine++;
			iCount++;
		}
		
		switch (iCount)
		{
		case 1:
			q_TileMapLayerBase.push(recordList[iLine]);
			break;
		case 2:
			q_TileMapLayerTile.push(recordList[iLine]);
			break;
		case 3:
			q_TileMapLayerObject.push(recordList[iLine]);
			break;
		}
		iLine++;
	}
	recordList.clear();
}
