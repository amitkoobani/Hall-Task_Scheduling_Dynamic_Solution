#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <chrono>
#include <numeric>
#include <algorithm>

using namespace std;
const int INFINITY_VALUE = numeric_limits<int>::max(); // Using the maximum value of int as a sentinel for infinity

int EVS(vector<int>& JobsDuration , int DueDate)
{
	sort(JobsDuration.begin(), JobsDuration.end());

	const int num_jobs = JobsDuration.size();
	vector<int> row(DueDate + 1, 0);
	vector<vector<int>> F_ka(num_jobs + 1, row);

	for (int i = 0; i <= DueDate; i++) {
		if (i != DueDate)
			F_ka[0][i] = INFINITY_VALUE;
	}

	int left_arg;
	int right_arg;
	vector<int> partialSums(num_jobs);

	// Calculate partial sums and insert into a vector
	partial_sum(JobsDuration.begin(), JobsDuration.end(), partialSums.begin());	

	for (int k = 1; k <= num_jobs; ++k) {
		for (int a = 0; a <= DueDate; ++a) {

			if (partialSums[num_jobs - k] > a && a + JobsDuration[num_jobs - k] <= DueDate)
			{
				if (F_ka[k - 1][a + JobsDuration[num_jobs - k]] == INFINITY_VALUE)
					left_arg = INFINITY_VALUE;
				else
					left_arg = a + F_ka[k - 1][a + JobsDuration[num_jobs - k]];

				if (F_ka[k - 1][a] == INFINITY_VALUE)
					right_arg = INFINITY_VALUE;
				else
					right_arg = partialSums[(num_jobs)-k] - a + F_ka[k - 1][a];
			

			F_ka[k][a] = min(left_arg, right_arg);

			/*if (a + JobsDuration[num_jobs - k] > DueDate ||
				F_ka[k - 1][a + JobsDuration[num_jobs - k]] == INFINITY_VALUE)

				left_arg = INFINITY_VALUE;
			else
				left_arg = a + F_ka[k - 1][a + JobsDuration[num_jobs - k]];*/
			}

			else if (partialSums[num_jobs - k] <= a && a + JobsDuration[num_jobs - k] <= DueDate) {
				
				if (F_ka[k - 1][a + JobsDuration[num_jobs - k]] == INFINITY_VALUE)
					F_ka[k][a] = INFINITY_VALUE;
				else
					F_ka[k][a] = a + F_ka[k - 1][a + JobsDuration[num_jobs - k]];
			}

			else
				F_ka[k][a] = INFINITY_VALUE;
			
			/*if (F_ka[k - 1][a] == INFINITY_VALUE)
				right_arg = INFINITY_VALUE;
			else
				right_arg = partialSums[(num_jobs)-k] - a + F_ka[k - 1][a];*/
		}	
	}
	
	std::vector<int>& last_row = F_ka.back();

	// Find the minimum element in the last row
	auto min_element_it = std::min_element(last_row.begin(), last_row.end());
	return *min_element_it;
}

int TVS(vector<int>& JobsDuration, int DueDate) {

	sort(JobsDuration.begin(), JobsDuration.end());
	
	const int sum_jobs = std::accumulate(JobsDuration.begin(), JobsDuration.end(), 0);
	const int num_jobs = JobsDuration.size();
	int p_minus_d = sum_jobs - DueDate;


	vector<int> row(p_minus_d +1, 0);
	vector<vector<int>> G_km(num_jobs + 1, row);

	for (int i = 0; i <= p_minus_d; i++) {
		if (i != p_minus_d)
			G_km[0][i] = INFINITY_VALUE;
	}

	int left_arg;
	int right_arg;
	vector<int> partialSums(num_jobs);

	// Calculate partial sums and insert into a vector
	partial_sum(JobsDuration.begin(), JobsDuration.end(), partialSums.begin());

	for (int k = 1; k <= num_jobs; ++k) {
		for (int m = 0; m <= p_minus_d; ++m) {

			if (partialSums[num_jobs - k] > m && m + JobsDuration[num_jobs - k] <= p_minus_d)
			{
				if (G_km[k - 1][m + JobsDuration[num_jobs - k]] == INFINITY_VALUE)
					left_arg = INFINITY_VALUE;
				else
					left_arg = m + G_km[k - 1][m + JobsDuration[num_jobs - k]] 
					+ JobsDuration[num_jobs -k];

				if (G_km[k - 1][m] == INFINITY_VALUE)
					right_arg = INFINITY_VALUE;
				else
					right_arg = abs(partialSums[(num_jobs)-k-1] - m ) + G_km[k - 1][m];


				G_km[k][m] = min(left_arg, right_arg);

				/*if (a + JobsDuration[num_jobs - k] > DueDate ||
					G_km[k - 1][a + JobsDuration[num_jobs - k]] == INFINITY_VALUE)

					left_arg = INFINITY_VALUE;
				else
					left_arg = a + G_km[k - 1][a + JobsDuration[num_jobs - k]];*/
			}

			else if (partialSums[num_jobs - k] <= m && m + JobsDuration[num_jobs - k] <= DueDate) {

				if (G_km[k - 1][m + JobsDuration[num_jobs - k]] == INFINITY_VALUE)
					G_km[k][m] = INFINITY_VALUE;
				else
					G_km[k][m] = m + G_km[k - 1][m + JobsDuration[num_jobs - k]] 
					+ JobsDuration[num_jobs - k];
			}

			else
				G_km[k][m] = INFINITY_VALUE;

			/*if (G_km[k - 1][a] == INFINITY_VALUE)
				right_arg = INFINITY_VALUE;
			else
				right_arg = partialSums[(num_jobs)-k] - a + G_km[k - 1][a];*/
		}
	}

	std::vector<int>& last_row = G_km.back();

	// Find the minimum element in the last row
	auto min_element_it = std::min_element(last_row.begin(), last_row.end());
	return *min_element_it;
}

int Nosplit(vector<int>& JobsDuration, int DueDate) {

	sort(JobsDuration.begin(), JobsDuration.end());

	const int num_jobs = JobsDuration.size();
	vector<int> row(DueDate + 1, INFINITY_VALUE);
	vector<vector<int>> H_ke(num_jobs + 1, row);
	H_ke[0][0] = 0;

	int left_arg;
	int right_arg;
	vector<int> partialSums(num_jobs);

	// Calculate partial sums and insert into a vector
	partial_sum(JobsDuration.begin(), JobsDuration.end(), partialSums.begin());

	for (int k = 1; k <= num_jobs; ++k) {
		for (int e = 0; e <= DueDate; ++e) {

			if (e >= JobsDuration[k - 1]) {
				if (H_ke[k - 1][e - JobsDuration[k - 1]] == INFINITY_VALUE)
					left_arg = INFINITY_VALUE;
				else
					left_arg = e - JobsDuration[k - 1] + H_ke[k - 1][e - JobsDuration[k - 1]];

				if (H_ke[k - 1][e] == INFINITY_VALUE)
					right_arg = INFINITY_VALUE;
				else
					right_arg = H_ke[k - 1][e] - e + partialSums[k-1];

				H_ke[k][e] = min(right_arg, left_arg);
			}

			else {
				
				if (H_ke[k - 1][e] == INFINITY_VALUE)
					H_ke[k][e] = INFINITY_VALUE;
				else
					H_ke[k][e] = partialSums[k - 1] - e + H_ke[k - 1][e];
			}
		
		}

	}
	std::vector<int>& last_row = H_ke.back();

	// Find the minimum element in the last row
	auto min_element_it = std::min_element(last_row.begin(), last_row.end());
	return *min_element_it;
}


vector<int> initializeVector(int size, int minValue, int maxValue) {
	vector<int> result(size);
	for (int i = 0; i < size; ++i) {
		result[i] = rand() % (maxValue - minValue + 1) + minValue;
	}
	return result;
}



int Optcet(vector<int>& JobsDuration, int DueDate) {
	
	sort(JobsDuration.begin(), JobsDuration.end());

	const int num_jobs = JobsDuration.size();
	int sum_result = 0;
	int cost = 0;

	for (int i = num_jobs - 1; i >= 0; i -= 2 ) {
		sum_result += JobsDuration[i];
	}
	if (sum_result <= DueDate) {

		for (int i = 0; i < num_jobs; i++) {
			cost += ((i + 1) / 2) * JobsDuration[num_jobs - 1 - i];
		}
		cout << "the minimum price is: " << cost << endl;
		return cost;
	}
	if (DueDate <= JobsDuration[0]){
		for(int i = 0; i < num_jobs; i++) {
			cost += (num_jobs-i) * JobsDuration[i];
		}
		cost -= num_jobs * DueDate;
		cout << "the minimum price is: " << cost << endl;
		return cost;
	}
	int evs_price = EVS(JobsDuration, DueDate);
	int tvs_price = TVS(JobsDuration, DueDate);
	int nosplit_price = Nosplit(JobsDuration, DueDate);

	cout << "the minimum price in EVS is:" << evs_price << endl;
	cout << "the minimum price in TVS is:" << tvs_price << endl;
	cout << "the minimum price in Nosplit is:" << nosplit_price << endl;

	cout << "the minimum price is: " << min(evs_price, min(tvs_price, nosplit_price)) << endl;

	return min(evs_price, min(tvs_price, nosplit_price));
}


int main()
{
	//srand(static_cast<unsigned int>(time(nullptr)));

	vector<int> JobsDuration = {1,3,7,8,8,9};
	int d = 14;

	//vector<int> JobsDuration = { 1,3,7,8,8,9 };
	//int d = 24;

	//std::vector<int> JobsDuration = {2, 3, 3, 5, 7};
	//int d = 13;

	int result = Optcet(JobsDuration, d);

	return 0;
}