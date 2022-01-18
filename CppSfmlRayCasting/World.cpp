#include "World.h"
#include "Settings.h"

using namespace gst;
using namespace std;
using namespace sf;

World::World() = default;

void World::loadMap(const string & path) {
	Image map;
	map.loadFromFile(MAP_FILE_LOCATION);

	unsigned width = map.getSize().x;
	unsigned height = map.getSize().y;

	_mappedWorld = vector<vector<WorldBloc>>(width, vector<WorldBloc>(height));

	for (int x = 0; x < width; ++x) {
		float posX = x * WORLD_BLOC_SIZE;

		for (int y = 0; y < height; ++y) {
			Color color = map.getPixel(x, y);

			Vector2f pos(posX, y * WORLD_BLOC_SIZE);
			Vector2i gridPos(x, y);

			WorldBloc bloc(pos, color, WORLD_BLOC_SIZE, gridPos);

			_mappedWorld[x][y] = bloc;

			if (bloc.getType() != WorldBlocType::BACKGROUND) {
				_blocs.push_back(bloc);
			}
		}
	}
}

WorldBloc& World::getBloc(Vector2i pos) {
	return _mappedWorld.at(pos.x).at(pos.y);
}

WorldBloc& World::getBloc(Vector2f pos) {
	int x = int(pos.x / WORLD_BLOC_SIZE);
	int y = int(pos.y / WORLD_BLOC_SIZE);

	return getBloc(Vector2i(x, y));
}

vector<WorldBloc>& World::getBlocs() {
	return _blocs;
}