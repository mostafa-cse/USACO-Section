bool isSafe(vector<int> Available, vector<vector<int>> Max, vector<vector<int>> Allocation) {
    int n = Allocation.size();      // Number of Processes
    int m = Available.size();       // Number of Resource Types

    vector<vector<int>> Need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    vector<bool> Finish(n, false);
    vector<int> Work = Available;
    vector<int> SafeSeq;

    while (true) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];
                    Finish[i] = true;
                    SafeSeq.push_back(i);
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    for (bool done : Finish)
        if (!done) return false;  // Deadlock

    // Optional: print Safe Sequence
    cout << "Safe Sequence: ";
    for (int p : SafeSeq) cout << "P" << p << " ";
    cout << endl;

    return true; // Safe State
}
