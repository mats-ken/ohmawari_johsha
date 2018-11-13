#include	"stdafx.h"

#include	<algorithm>
#include	<iostream>
#include	<fstream>
#include	<string>
#include	<sstream>
#include	<map>
#include	<vector>


using	namespace	std;


static	int		read_data(
	const string		&	path,
	vector<string>		&	station_vec,
	map<string, int>	&	station_map,
	vector<vector<int>>	&	matrix
) {
	ifstream	ifs(path);
	if (!ifs.is_open()) {
		return	-1;
	}

	string	line;

	// read legends
	getline(ifs, line);
	istringstream	s(line);

	int		n = 0;
	string	token;
	while (getline(s, token, ',')) {
		station_vec.push_back(token);
		station_map[token] = n++;
	}

	// read data
	while (getline(ifs, line)) {
		istringstream	s(line);

		string	token;
		vector<int>		row;
		while (getline(s, token, ',')) {
			if (("*" != token) && ("" != token)) {
				row.push_back(stoi(token));
			} else {
				row.push_back(0);
			}
		}
		while (row.size() < station_vec.size()) {
			row.push_back(0);
		}
		matrix.push_back(row);
	}

	return	0;
}


void	search_routes(
	const	vector<vector<int>>	&	matrix,
	const	int						n,
	const	int						max_transfers,
			vector<int>				route,
			vector<vector<int>>	&	routes
) {
	if (max_transfers + 1 < route.size()) {
		return;
	}

	if (2 < route.size() && route[0] == n) {
		route.push_back(n);
		routes.push_back(route);
		return;
	}

	if (0 < route.size() && route[route.size() - 1] == n) {
		return;
	}

	if (find(route.begin(), route.end(), n) != route.end()) {
		return;
	}

	route.push_back(n);

	for (int i = 0; i < (int)matrix[n].size(); i++) {
		if (0 < matrix[n][i]) {
			search_routes(
				matrix,
				i,
				max_transfers,
				route,
				routes);
		}
	}
}


int		main(const int argc, const char*const argv[])
{
	vector<string>			station_vec;
	map<string, int>		station_map;
	vector<vector<int>>		matrix;

	if (argc <= 1) {
		cerr << "Too few args." << endl;
		return	EXIT_FAILURE;
	}

	// read adjacency matrix
	if (read_data(argv[1], station_vec, station_map, matrix) < 0) {
		cerr << "File open error." << endl;
		return	EXIT_FAILURE;
	}

	int		max_transfers = 10;
	if (3 <= argc) {
		max_transfers = atoi(argv[2]);
	}

	vector<int>		starting_points;
	if (4 <= argc) {
		for (int i = 3; i < argc; i++) {
			starting_points.push_back(station_map.at(argv[i]));
		}
	} else {
		for (int i = 0; i < (int)station_vec.size(); i++) {
			starting_points.push_back(i);
		}
	}

	vector<vector<int>>		routes;
	for (int i : starting_points) {
		vector<int>				route;
		search_routes(matrix, i, max_transfers, route, routes);
	}

	for (auto route : routes) {
		for (int n : route) {
			cout << station_vec[n] << ",";
		}
		cout << endl;
	}

	return	EXIT_SUCCESS;
}
