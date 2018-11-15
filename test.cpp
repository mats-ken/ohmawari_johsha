#include	<algorithm>
#include	<iostream>
#include	<string>
#include	<vector>


using	namespace	std;


void	search_routes(
	const	vector<vector<int>>	&	matrix,
	const	int						n,
			vector<int>				route,
			vector<vector<int>>	&	routes
) {
	if ((2 < route.size()) && (route[0] == n)) {
		route.push_back(n);
		routes.push_back(route);
		return;
	}

	if ((0 < route.size()) && (route[route.size() - 1] == n)) {
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
				route,
				routes);
		}
	}
}


int		main(void)
{
	vector<string>			names;
	vector<vector<int>>		matrix;

	names = { "A", "B", "C", "D" };
	matrix.push_back(vector<int>{ 0, 1, 0, 1 });
	matrix.push_back(vector<int>{ 1, 0, 1, 1 });
	matrix.push_back(vector<int>{ 0, 1, 0, 1 });
	matrix.push_back(vector<int>{ 1, 1, 1, 0 });

	vector<int>				route;
	vector<vector<int>>		routes;

	for (int i = 0; i < (int)names.size(); i++) {
		search_routes(matrix, i, route, routes);
	}

	for (auto route : routes) {
		for (int n : route) {
			cout << names[n];
		}
		cout << endl;
	}

	return	0;
}
