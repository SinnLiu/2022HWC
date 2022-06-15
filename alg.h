typedef unsigned int Uint;
typedef unsigned long long Ulong;

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

time_t star_time = clock();
time_t end_time = clock();

struct {
  Uint CoreStream_K, WorkShop_N, Zone_R, MaxLoop_L, FirstLoopNum, WinNum,
      MachiNum, StreamSide, CoreStreamSide;
  vector<Uint> WorkTime, CoreStreamIndex, FrontMachi, BackMachi, CoreMachi, CoreMachiIndexSort;
  vector<vector<Uint>> ZoneInfo, WinInfo, MachiInfo, StreamSideInfo;

} Inp;

struct {
  Uint CoreStepNum, MachiNum;
  vector<Uint> Machi_ZoneIndex, Machi_WorkTime, CoreStream_WinIndex, WinInTimes,
      WorkTime, WinFeeeCoeff, TotalTime, WinPreFree;
  vector<Ulong> InstallFreevector, PreFreevector;
  Ulong InstallFree, PreFree, TotalFree,Anstempmin, AnstempminCore, NonCoreInstallFree, CoreFree;

  vector<set<Uint>> WinWorkTime;

} Outp;

int map_Machine_Power[3][2] = {{0, 1}, {0, 2}, {3, 4}};

typedef struct Workshop {
  int id;
  int group;
  int power_type;
} Workshop;

typedef struct Window {
  int id;
  bool loop;
  int group_id;
  int cost;
  bool ability[3];
  list<int> power_type;
} Window;

typedef struct Machine {
  int id;
  int type;
  int cost[5];
  list<int> Access_window;   // 可分配的窗口
  list<int> Access_workshop; //可分配的车间区域
  bool assign;
  int workshop_id;
  int window_id; // 分配的窗口id（相对于最长窗口）
  bool iscore;
  // 仪器自身维护一个有向无环图
  list<int> adj;         // 邻接表
  vector<int> prev;      // 记录该仪器的所有前驱仪器
  vector<int> link_type; // 记录链接类型
  int indegree;          // 入度
} Machine;

typedef struct Workflow {
  int type;
  int prev;
  int next;
} Workflow;

typedef struct pair_Machine_Workshop {
  int prev;
  int prev_workshop;
  int next;
  int next_workshop;
} pair_Machine_Workflow;

typedef struct Window_Assign_Tree {
  int window_id;
  list<Window_Assign_Tree *> next;
} Window_Assign_Tree;

vector<int> create_max_len_window_link(Window *windows, int window_len, int L,
                                       int type_cicle_1) {
  vector<int> window_link;
  for (int iter = 0; iter <= L; iter++)
    for (int idx = 0; idx < type_cicle_1; idx++)
      window_link.push_back(idx);
  for (int idx = type_cicle_1; idx < window_len; idx++) {
    if (windows[idx].loop) {
      for (int iter = 0; iter <= L; iter++)
        window_link.push_back(idx);
    } else
      window_link.push_back(idx);
  }
  return window_link;
};

// 构造窗口分配方案树
void creat_window_assign_tree(Window_Assign_Tree *root, stack<Machine> machines,
                              vector<int> window_link, stack<int> link_types,
                              int begin) {
  if (machines.empty())
    return;
  Machine m = machines.top();
  machines.pop();
  int type = link_types.top();
  link_types.pop();
  for (auto win_idx : m.Access_window) {
    int j = type ? begin : begin + 1;
    while (window_link[j] != win_idx && j < window_link.size() - 1)
      j++;
    if (window_link[j] != win_idx)
      continue;
    Window_Assign_Tree *node = new Window_Assign_Tree;
    node->window_id = win_idx;
    root->next.push_back(node);
    creat_window_assign_tree(node, machines, window_link, link_types, j);
  }
};
// 构造区域分配方案树
void creat_workshop_assign_tree(Window_Assign_Tree *root, queue<Machine> machines) {
  if (machines.empty())
    return;
  Machine m = machines.front();
  machines.pop();
  for (auto workshop_idx : m.Access_workshop) {
    Window_Assign_Tree *node = new Window_Assign_Tree;
    node->window_id = workshop_idx;
    root->next.push_back(node);
    creat_workshop_assign_tree(node, machines);
  }
};
// 返回所有和核心流水线长度一致的树的路径
bool find_core_window(Window_Assign_Tree *root, vector<vector<int>> &path,
                      int layer, int target) {
  if (layer == target) {
    vector<int> temp;
    temp.push_back(root->window_id);
    path.push_back(temp);
    return true;
  }
  if (root->next.size() == 0)
    return false;
  bool return_flag = false;
  for (auto node : root->next) {
    vector<vector<int>> temp_path;
    bool flag = find_core_window(node, temp_path, layer + 1, target);
    if (flag) {
      for (auto sub_temp_path : temp_path)
        path.push_back(sub_temp_path);
      return_flag = true;
    }
  }
  if (return_flag)
    for (auto &subpath : path)
      subpath.push_back(root->window_id);
  return return_flag;
};

bool find_core_window(Window_Assign_Tree *root, int layer, int target) {
  if (layer == target)
    return true;
  if (root->next.size() == 0)
    return false;
  bool return_flag = false;
  for (auto node : root->next) {
    bool flag = find_core_window(node, layer + 1, target);
    if (flag) {
      return_flag = true;
    }
  }
  return return_flag;
};

void tree_node(Window_Assign_Tree *root) {
  for (auto node : root->next) {
    tree_node(node);
  }
  cout << root->window_id << endl;
};

//--------------------------------------------------------------------

vector<Uint> Creat_CoreMachi(vector<Uint> streamindex) {
  vector<Uint> coremachi;
  for (int i = 0; i < Inp.StreamSide; i++) {
    Inp.FrontMachi.push_back(Inp.StreamSideInfo[i][1]);
    Inp.BackMachi.push_back(Inp.StreamSideInfo[i][2]);
  }

  for (auto n : streamindex) {
    coremachi.push_back(Inp.FrontMachi[n]);
  }
  coremachi.push_back(Inp.BackMachi[streamindex.back()]);
  //    cout<<"CoreMachi!"<<endl;
  //    for(auto nm:coremachi) cout<<nm<<' ';cout<<endl;
  return coremachi;
}

Ulong Cost(vector<Uint> machi_zone, vector<Uint> machi_win)
{
  Outp.CoreStepNum = Inp.CoreStreamSide + 1;
  Outp.MachiNum = Inp.MachiNum;

  Outp.InstallFreevector.clear();
  Outp.WinWorkTime.clear();
  Outp.WorkTime.clear();
  Outp.PreFreevector.clear();

  Outp.InstallFree = 0;
  Outp.NonCoreInstallFree=0;
  Outp.CoreFree=0;

  /*
      cout<<"**********************************"<<endl;
       cout<<"CostFreeCalculation"<<endl;*/
  //vector<Uint> machi_zone_example{0, 2, 1, 4, 3, 5, 1, 1, 4, 7, 1, 6, 6};
  //Outp.Machi_ZoneIndex = machi_zone_example;
  Outp.Machi_ZoneIndex = machi_zone;

  /*  for(auto n:Outp.Machi_ZoneIndex)
        cout<<n<<' ';
    cout<<endl;*/
  //vector<Uint> machi_win_example{0, 1, 0, 0, 1, 3, 4};
  //Outp.CoreStream_WinIndex = machi_win_example;
  Outp.CoreStream_WinIndex = machi_win;
  /*
      for(auto n:Outp.CoreStream_WinIndex)
          cout<<n<<' ';
      cout<<endl;
  */

  for (int i = 0; i < Outp.MachiNum; i++) {
    Uint zonetemp = Outp.Machi_ZoneIndex[i];
    Uint energytype = Inp.ZoneInfo[zonetemp][1];
    Outp.InstallFreevector.push_back(Inp.MachiInfo[i][energytype + 1]);
    Outp.InstallFree += Outp.InstallFreevector.back();
  /*  if(find(Inp.CoreMachi.begin(),Inp.CoreMachi.end(),i)==Inp.CoreMachi.end())
    {
      Outp.NonCoreInstallFree += Outp.InstallFreevector.back();
    }*/

  }
  //**********************************************************
  vector<Uint> WinInTimestemp(Inp.WinNum);
  Outp.WinInTimes = WinInTimestemp;
  //    for(auto nts:WinInTimes)
  //        cout<<nts<<' ';
  //    cout<<endl;
  for (int itwin = 0; itwin < Inp.WinNum; itwin++) {
    set<Uint> WinWorkTimeTemp;
    for (int itmachi = 0; itmachi < Outp.CoreStream_WinIndex.size();
         itmachi++) {
      if (itwin == Outp.CoreStream_WinIndex.at(itmachi)) {
        Outp.WinInTimes[itwin]++;
        Uint ZoneTemp = Outp.Machi_ZoneIndex.at(Inp.CoreMachi.at(itmachi));
        Uint EnergyTemp = Inp.ZoneInfo[ZoneTemp][1];
        WinWorkTimeTemp.insert(Inp.WorkTime.at(EnergyTemp));

        if (itmachi < Outp.CoreStream_WinIndex.size() - 1) {
          Uint SideType = Inp.StreamSideInfo[Inp.CoreStreamIndex[itmachi]][0];
          //                    cout<<"SideType:"<<SideType<<endl;
          if (SideType == 1 && Outp.CoreStream_WinIndex[itmachi] ==
                                   Outp.CoreStream_WinIndex[itmachi + 1])
            Outp.WinInTimes[itwin]--;
        }
      }
    }
    Outp.WinWorkTime.push_back(WinWorkTimeTemp);
  }

  //    for(auto nt:WinWorkTime)
  //    {
  //        for(auto setnt:nt)
  //            cout<<setnt<<' ';
  //        cout<<endl;
  //    }
  //    for(auto nts:WinInTimes)
  //        cout<<nts<<' ';
  //    cout<<endl;

  Ulong SumWorkTime = 0;
  Outp.PreFree = 0;

  for (int it = 0; it < Inp.WinNum; it++) {
    Uint Sumtemp = 0;
    Uint Pretemp = 0;
    if (Outp.WinInTimes.at(it) != 0) {
      Uint WinWorkTimeTemp = *Outp.WinWorkTime[it].rbegin();
      Uint WinInTimesTemp = Outp.WinInTimes.at(it);

      Sumtemp = WinWorkTimeTemp * WinInTimesTemp;
      Pretemp = WinWorkTimeTemp * Inp.WinInfo[it][2];
    }
    Outp.WorkTime.push_back(Sumtemp);
    SumWorkTime += Sumtemp;

    Outp.PreFreevector.push_back(Pretemp);
    Outp.PreFree += Pretemp;
  }

  Outp.TotalFree =
      SumWorkTime * Inp.CoreStream_K + Outp.PreFree + Outp.InstallFree;

 // Outp.CoreFree = Outp.TotalFree - Outp.NonCoreInstallFree;

  /*
      cout<<"InstallFreevector  ";
          for(auto n:Outp.InstallFreevector) cout<<n<<' '; cout<<endl;
      cout<<"Total InstallFree  "<<Outp.InstallFree<<endl;


      cout<<"WinWorkTime  ";
          for(int it=0;it<Inp.WinNum;it++)
          {
                  Uint temp = 0;
                  if(!Outp.WinWorkTime[it].empty()) temp =
     *Outp.WinWorkTime[it].rbegin(); cout<<temp<<' ';
          }
          cout<<endl;

          cout<<"Outp.WinInTimes  ";
          for(auto wit:Outp.WinInTimes) cout<<wit<<' ';cout<<endl;

          cout<<"WorkTime  ";
      for(auto nt:Outp.WorkTime) cout<<nt<<' '; cout<<endl;

          cout<<"SumWorkTime  ";
      cout<<SumWorkTime<<endl;

      cout<<"PreFreevector  ";
      for(auto nt:Outp.PreFreevector) cout<<nt<<' '; cout<<endl;

      cout<<"PreFree  ";
      cout<<Outp.PreFree<<endl;

      cout<<"TotalFree  ";
      cout<<Outp.TotalFree<<endl;
      cout<<"**********************************"<<endl;
  */
  return Outp.TotalFree;
}

vector<Uint> VectorEnum(vector<vector<Uint>> machizone, vector<Uint> maybezonesolOrigin, vector<Uint> coremachiwinindex)
{
    //vector<vector<Uint>> solution;
    vector<Uint> solutiontemp, maybezonesol = maybezonesolOrigin;
    vector<Uint> solutiontempAll = maybezonesolOrigin;
    //cout<<"Orgin_solutiontempAll:"<<endl;
    //for(auto n:solutiontempAll) cout<<n<<' ';cout<<endl;
    //Ulong Anstempmin = -1;

    //    vector<Uint> coremachi=Creat_CoreMachi(streamIndex);
    vector<Uint> totalstep(machizone.size());
    Uint itstep = 0;
    int itwl = 0;
    int itwm = 0;
    //    bool FindMW=false;
    //    cout<<"CreatMaybySolution"<<endl;
    while (1)
    {
        for (; itwl < machizone.size(); itwl++)
        {
            for (itwm = totalstep[itstep]; itwm < machizone[itstep].size(); itwm++)
            {
                //                if(machi_win[coremachi[itstep]].at(itwm)==winlink.at(itwl))
                //                {
                solutiontemp.push_back(machizone[itwl][itwm]);
                //                    if(itstep<streamIndex.size())
                //                    if(StreamSideInfo[itstep][0]==1)
                //                    itwl--;//Coordination
                totalstep[itstep++] = itwm + 1;
                //                    if(itstep==coremachi.size()) FindMW = true;
                break;
                //                }
            }

            if (0 < itstep && itstep < machizone.size())
            {
                if (itwl < machizone.size() - 1)
                {
                    continue;
                }
                else if (itwl == machizone.size() - 1)
                {
                    totalstep[itstep--] = 0;
                    Uint tempback = solutiontemp.back();
                    solutiontemp.pop_back();

                    if (!solutiontemp.empty())
                    {
                        int ct = itwl - itstep;
                        //                      cout<<"ct"<<ct<<endl;
                        do
                        {
                            itwl--;
                        }
                        while (ct--);
                    }
                    else
                    {
                        itwl = -1;
                    }
                }
            }
            else if (itstep == machizone.size())
            {
                //                if(FindMW)
                //                {
                //solution.push_back(solutiontemp);
                //cout<<"maybeCoreZone"<<endl;
                //for(auto cm:solutiontemp) cout<<cm<<' ';cout<<endl;

                for(int i=0;i<Inp.CoreMachiIndexSort.size();i++)
                {
                    solutiontempAll[Inp.CoreMachiIndexSort[i]] = solutiontemp[i];
                }
                //cout<<"Update_solutiontempAll:"<<endl;
                //for(auto n:solutiontempAll) cout<<n<<' ';cout<<endl;

                Ulong Anstemp = Cost(solutiontempAll, coremachiwinindex);
                //cout<<Anstemp<<endl;
                if (Outp.Anstempmin > Anstemp)
                {
                    Outp.Anstempmin = Anstemp;
                    maybezonesol = solutiontempAll;
                }

                end_time = clock();
                if((double)(end_time - star_time)/CLOCKS_PER_SEC>13.0)
                    return maybezonesol;
                //                    for(auto n:solutiontemp) cout<<n<<' ';cout<<endl;
                solutiontemp.pop_back();
                itwl--;
                --itstep;
                //                }
            }
            else if (itstep == 0)
            {
                //                cout<<"itstep==0"<<endl;
                break;
            }
        }

        if (itstep == 0 && itwm == machizone[itstep].size())
        {
            //          cout<<"while Done!"<<endl;
            break;
        }
    }
    /*
        cout<<"VectorEnum"<<endl;
        for(int i=0; i<solution.size(); i++)
        {
            for(auto n2:solution[i])
                cout<<n2<<' ';
            cout<<endl;
        }
    */
    return maybezonesol;
}

vector<Uint> MachitoZone(vector<Uint> maybewinsol,
                         vector<Uint> coremachiwinindex)
{
    vector<Uint> maybezonesol;
    vector<vector<Uint>> Allmaybezonesol;


    for (int im = 0; im < Inp.MachiNum; im++)
    {
        vector<Uint> machizonetemp;
        Uint wintemp = maybewinsol[im];
        Uint workshop = Inp.WinInfo[wintemp][1];
        Uint machitype = Inp.MachiInfo[im][0];
        //  cout<<im<<' '<<wintemp<<' '<<workshop<<' '<<machitype<<endl;
        for (int iz = 0; iz < Inp.Zone_R; iz++)
        {

            if (workshop == Inp.ZoneInfo[iz][0])
            {

                Uint zoneenergy = Inp.ZoneInfo[iz][1];
                // cout<<iz<<endl;cout<<zoneenergy<<endl;
                if (machitype == 0)
                {
                    if (zoneenergy == 0 || zoneenergy == 1)
                    {
                        machizonetemp.push_back(iz);
                        continue;
                    }
                }
                else if (machitype == 1)
                {
                    if (zoneenergy == 0 || zoneenergy == 2)
                    {
                        machizonetemp.push_back(iz);
                        continue;
                    }
                }
                else
                {
                    if (zoneenergy == 3 || zoneenergy == 4)
                    {
                        machizonetemp.push_back(iz);
                        continue;
                    }
                }
            }
        }
        //  cout<<"machi "<<im<<endl;
        //  for(auto n:machizonetemp) cout<<n<<' ';cout<<endl;

        if(find(Inp.CoreMachi.begin(),Inp.CoreMachi.end(),im)!=Inp.CoreMachi.end())
        {
          Allmaybezonesol.push_back(machizonetemp);
          //cout<<"im"<<im<<endl;
          Inp.CoreMachiIndexSort.push_back(im);
          //for(auto n:machizonetemp) cout<<n<<' ';cout<<endl;
        }



        Uint mz = machizonetemp[0];
        Uint enez = Inp.ZoneInfo[mz][1];
        Uint minfree = Inp.MachiInfo[im][1+enez];
        for(int itz=1; itz<machizonetemp.size(); itz++)
        {
            Uint mztemp=machizonetemp[itz];
            Uint eneztemp=Inp.ZoneInfo[mztemp][1];
            Uint minfreetemp = Inp.MachiInfo[im][1+eneztemp];
            if(minfreetemp<minfree)
            {
                minfree=minfreetemp;
                mz=mztemp;
            }
        }

        maybezonesol.push_back(mz);

    }
    Outp.Anstempmin = Cost(maybezonesol, coremachiwinindex);
    Outp.AnstempminCore = Outp.CoreFree;

    /*
      vector<vector<Uint>> Allmaybezone =
          VectorEnum(Allmaybezonesol, coremachiwinindex);

      Ulong Anstempmin = -1;
      for (auto nsole : Allmaybezone) {
        Ulong Anstemp = Cost(nsole, coremachiwinindex);
        if (Anstempmin > Anstemp) {
          Anstempmin = Anstemp;
          maybezonesol = nsole;
        }
      }
    */

    maybezonesol = VectorEnum(Allmaybezonesol, maybezonesol, coremachiwinindex);
    return maybezonesol;
}

