#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "alg.h"
using namespace std;

//typedef unsigned int Uint;
//typedef unsigned long Ulong;



int main(int argc, char *argv[])
{

    //string Inpath = "case0.in";//Linux
    // string Inpath = "D:\\Codeblocks\\Cplusplus\\Huawei_embedded\\case0.in";//Windows
    //ifstream fin;

    //fin.open(Inpath);
    string data;
    stringstream string_stream;
    string temp;
   /* if(!fin)
    {
        cout<<"a"<<endl;
        return -1;
    }*/

//1
    getline(cin,data);
    Inp.CoreStream_K = stoi(data);

//2
    getline(cin,data);
    string_stream << data;
    while(getline(string_stream,temp,' '))
    {
        Inp.WorkTime.push_back(stoi(temp));
    }
    string_stream.str("");
    string_stream.clear(ios::goodbit);

//3
    getline(cin,data);
    Inp.WorkShop_N = stoi(data);

//4
    getline(cin,data);
    Inp.Zone_R = stoi(data);

//5
    for(int i=0; i < Inp.Zone_R; i++)
    {
        getline(cin,data);
        stringstream string_stream(data);
        vector<Uint> temp_2;
        while(getline(string_stream,temp,' '))
        {
            temp_2.push_back(stoi(temp));
        }
        Inp.ZoneInfo.push_back(temp_2);
    }

//6
    getline(cin,data);
    Inp.MaxLoop_L = stoi(data);

//7
    getline(cin,data);
    Inp.FirstLoopNum = stoi(data);

//8
    getline(cin,data);
    Inp.WinNum = stoi(data);

//9
    for(int i=0; i < Inp.WinNum; i++)
    {
        getline(cin,data);
        stringstream string_stream(data);
        vector<Uint> temp_2;
        while(getline(string_stream,temp,' '))
        {
            temp_2.push_back(stoi(temp));
        }
        Inp.WinInfo.push_back(temp_2);
    }
//10
    getline(cin,data);
    Inp.MachiNum = stoi(data);

//11
    for(int i=0; i < Inp.MachiNum; i++)
    {
        getline(cin,data);
        stringstream string_stream(data);
        vector<Uint> temp_2;
        while(getline(string_stream,temp,' '))
        {
            temp_2.push_back(stoi(temp));
        }
        Inp.MachiInfo.push_back(temp_2);
    }

//12
    getline(cin,data);
    Inp.StreamSide = stoi(data);

//13
    for(int i=0; i < Inp.StreamSide; i++)
    {
        getline(cin,data);
        stringstream string_stream(data);
        vector<Uint> temp_2;
        while(getline(string_stream,temp,' '))
        {
            temp_2.push_back(stoi(temp));
        }
        Inp.StreamSideInfo.push_back(temp_2);
    }

//14
    getline(cin,data);
    Inp.CoreStreamSide = stoi(data);

//15
    getline(cin,data);
    string_stream << data;
    while(getline(string_stream,temp,' '))
    {
        Inp.CoreStreamIndex.push_back(stoi(temp));
    }
    string_stream.str("");
    string_stream.clear(ios::goodbit);


   // fin.close();


//**************************************************
/*
    cout<<"Input:"<<endl;
    cout<<Inp.CoreStream_K<<endl;
    for(int i=0; i<Inp.WorkTime.size(); i++)
    {
        cout <<Inp.WorkTime[i];
        if(i<Inp.WorkTime.size()-1)
            cout<<' ';
        else
            cout<<endl;
    }
    cout<<Inp.WorkShop_N<<endl;
    cout<<Inp.Zone_R<<endl;
    for(int i=0; i < Inp.Zone_R; i++)
    {
        for(int j=0; j<Inp.ZoneInfo[i].size(); j++)
        {
            cout<<Inp.ZoneInfo[i][j];
            if(j<Inp.ZoneInfo[i].size()-1)
                cout<<' ';
            else
                cout<<endl;
        }
    }
    cout<<Inp.MaxLoop_L<<endl;
    cout<<Inp.FirstLoopNum<<endl;
    cout<<Inp.WinNum<<endl;
    for(int i=0; i < Inp.WinNum; i++)
    {
        for(int j=0; j<Inp.WinInfo[i].size(); j++)
        {
            cout<<Inp.WinInfo[i][j];
            if(j<Inp.WinInfo[i].size()-1)
                cout<<' ';
            else
                cout<<endl;
        }
    }
    cout<<Inp.MachiNum<<endl;
    for(int i=0; i < Inp.MachiNum; i++)
    {
        for(int j=0; j<Inp.MachiInfo[i].size(); j++)
        {
            cout<<Inp.MachiInfo[i][j];
            if(j<Inp.MachiInfo[i].size()-1)
                cout<<' ';
            else
                cout<<endl;
        }
    }
    cout<<Inp.StreamSide<<endl;
    for(int i=0; i < Inp.StreamSide; i++)
    {
        for(int j=0; j<Inp.StreamSideInfo[i].size(); j++)
        {
            cout<<Inp.StreamSideInfo[i][j];
            if(j<Inp.StreamSideInfo[i].size()-1)
                cout<<' ';
            else
                cout<<endl;
        }
    }
    cout<<Inp.CoreStreamSide<<endl;
    for(int i=0; i<Inp.CoreStreamIndex.size(); i++)
    {
        cout <<Inp.CoreStreamIndex[i];
        if(i<Inp.CoreStreamIndex.size()-1)
            cout<<' ';
        else
            cout<<endl;
    }
    cout<<"*******************************"<<endl;
*/

    Outp.CoreStepNum = Inp.CoreStreamSide+1;

    Workshop workshops[Inp.Zone_R];
    for(int idx = 0; idx < Inp.Zone_R; idx++)
    {
            workshops[idx].id = idx;
            workshops[idx].group = Inp.ZoneInfo[idx][0], workshops[idx].power_type = Inp.ZoneInfo[idx][1];
    }
    // ��������
    Window windows[Inp.WinNum];
    for(int idx=0; idx < Inp.WinNum; idx++)
    {
        windows[idx].id = idx;
        windows[idx].loop = bool(Inp.WinInfo[idx][0]), windows[idx].group_id = Inp.WinInfo[idx][1],windows[idx].cost = Inp.WinInfo[idx][2];
        for(int k = 0 ; k < 3 ; k++)
            windows[idx].ability[k] = bool(Inp.WinInfo[idx][3+k]);
        // ͳ�ƴ���֧�ֵ���Դ���ƺ�����Ҫȥ��
        for(int idx_ws = 0; idx_ws < Inp.Zone_R; idx_ws++)
            if(workshops[idx_ws].group == windows[idx].group_id)
                windows[idx].power_type.push_back(workshops[idx_ws].power_type);
    }
    int cnt = 0;
    for(int idx=0; idx < Inp.WinNum; idx++)
	{
		if(windows[idx].loop)
			cnt++;
		if(cnt == 1)
			windows[idx].loop = false;
	}

    // ��ˮ��
    Workflow workflows[Inp.StreamSide];
	for(int idx = 0 ; idx < Inp.StreamSide ; idx++)
	{
		workflows[idx].type = Inp.StreamSideInfo[idx][0], workflows[idx].prev = Inp.StreamSideInfo[idx][1], workflows[idx].next = Inp.StreamSideInfo[idx][2];
    }
    // ��������
    Machine machines[Inp.MachiNum];
	for(int idx = 0 ; idx < Inp.MachiNum ; idx++)
	{
        //cout<<"Machi:"<<idx<<"  "<<endl;
		machines[idx].id = idx;
		machines[idx].assign = false;
		machines[idx].type = Inp.MachiInfo[idx][0];
        machines[idx].indegree = 0;
		for(int idx_cost = 0 ; idx_cost < 5 ; idx_cost++)
			machines[idx].cost[idx_cost] = Inp.MachiInfo[idx][1+idx_cost];
        // �������д���
        // ��Ҫ�ҵ�������ˮ���ϸ��ǵ�������
		/*
        bool iscore = false;
        for(auto i : core_workflows)
            if(workflows[i].prev == idx || workflows[i].next == idx)
            {
                iscore = true;
                break;
            }
		*/
        machines[idx].iscore = true;
        for(int idx_win = 0; idx_win < Inp.WinNum; idx_win++)
        {
            list<int> this_power_type = windows[idx_win].power_type;
            // ����������������ڵ�Ԥ�ӹ�����֧�����������ڶ�Ӧ�ĳ�����Դ����֧������
            //machines[idx].iscoreΪtrue��windows[idx_win].ability[machines[idx].type]��Ҫ��Ч
            if(((!machines[idx].iscore) || windows[idx_win].ability[machines[idx].type]) &&
                (this_power_type.end() != find(this_power_type.begin(),this_power_type.end(),map_Machine_Power[machines[idx].type][0]) ||
                (this_power_type.end() != find(this_power_type.begin(),this_power_type.end(),map_Machine_Power[machines[idx].type][1]))))
            {
                machines[idx].Access_window.push_back(idx_win);
            }
        }
        //cout<<endl;
	}
    // ������ˮ��Ϊ�������ǰ���ͺ��
	for(int idx = 0 ; idx < Inp.StreamSide ; idx++)
	{
        machines[workflows[idx].prev].adj.push_back(workflows[idx].next), machines[workflows[idx].next].indegree++;
        machines[workflows[idx].next].prev.push_back(workflows[idx].prev);
        machines[workflows[idx].next].link_type.push_back(workflows[idx].type);
	}



    vector<int> window_link = create_max_len_window_link(windows, Inp.WinNum, Inp.MaxLoop_L, Inp.FirstLoopNum);
    window_link.insert(window_link.begin(),-1); // �������ĸ��ڵ���Ҫ������Ҫ����-1

    // ˼·�������޻�ͼ��̰���㷨
    // �����޻�ͼ����������
    queue<int> q_node;
    list<int> log_g;
    for(int idx = 0 ; idx < Inp.MachiNum ; idx++)
    {
        if(0 == machines[idx].indegree)
            q_node.push(idx);
    }
    while(!q_node.empty())
    {
        int idx = q_node.front();
        q_node.pop();
        log_g.push_back(idx);
        // ������idxָ��Ķ������ȼ�1��������ȼ�Ϊ0�Ķ�����ջ
        for(auto next_idx : machines[idx].adj)
            if(!(--machines[next_idx].indegree))
                q_node.push(next_idx);
    }
    //for(auto n:log_g) cout<<n<<' ';cout<<endl;
    // ̰���㷨
    // �����������ô���
    for(auto machine_idx : log_g)
    {
        if(machines[machine_idx].prev.size() == 0)
        {
            vector<int> min_win_id;
            for(auto window_id_ab : machines[machine_idx].Access_window)
            {
                // ����ҵ���ɷ��䴰�ھ���idһ�µ����id
                int j = 1;
                while(window_link[j] != window_id_ab && j < window_link.size()-1) j++;
                if(window_link[j] != window_id_ab) // ����������id�ں���û���ҵ������������id
                    continue;
                min_win_id.push_back(j); // �������Դ���id�����ѡ���
            }
            int minValue = *min_element(min_win_id.begin(),min_win_id.end()); // �ҵ���С�Ĵ������id
            machines[machine_idx].window_id = minValue;
            continue;
        }
        int max_idx = -1; // ����ǰ���ڵ㴰�����id�����ֵ
        int type;
		// ��������ǰ���ڵ���ͬһ�����ڵ��ǲ�ͬ�������ͣ���һ��Ҫ���ȿ���������ϵ
        for(int prev = 0 ; prev < machines[machine_idx].prev.size() ; prev++)
        {
            int prev_idx = machines[machine_idx].prev[prev];
            if(machines[prev_idx].window_id >= max_idx)
            {
				if((machines[prev_idx].window_id == max_idx) &&
					(type == 0 && machines[machine_idx].link_type[prev] == 1))
					continue;
				else
				{
					max_idx = machines[prev_idx].window_id;
					type = machines[machine_idx].link_type[prev];
				}
            }
        }
        // �ڿɷ��䴰�ھ���id���ҵ����õ���Сid
        vector<int> min_win_id;
        for(auto window_id_ab : machines[machine_idx].Access_window)
        {
            // ����ҵ���ɷ��䴰�ھ���idһ�µ����id
            int j = type ? max_idx : max_idx + 1;
            while(window_link[j] != window_id_ab && j < window_link.size()-1) j++;
            if(window_link[j] != window_id_ab) // ����������id�ں���û���ҵ������������id
			    continue;
            min_win_id.push_back(j); // �������Դ���id�����ѡ���
        }
        int minValue = *min_element(min_win_id.begin(),min_win_id.end()); // �ҵ���С�Ĵ������id
        machines[machine_idx].window_id = minValue;
    }

    // ���������䷽��
    // �ڱ�������֮ǰ�������Ÿ���ÿ�����ڰ�����Դ��������
    vector<int> order_workshop;
    for(int idx = 0 ; idx < Inp.Zone_R ; idx ++)
        order_workshop.push_back(idx);
    for(int idx = 0 ; idx < Inp.Zone_R ; idx ++)
        for(int pos = idx ; pos < Inp.Zone_R-1 ; pos++)
        {
            if(Inp.WorkTime[workshops[order_workshop[pos]].power_type] > Inp.WorkTime[workshops[order_workshop[pos+1]].power_type])
            {
                int temp = order_workshop[pos];
                order_workshop[pos] = order_workshop[pos+1];
                order_workshop[pos+1] = temp;
            }
        }
    // ����̰���㷨
    for(auto idx = log_g.rbegin() ; idx != log_g.rend() ; ++idx)
    {
        int machine_idx = *idx;
        if(machines[machine_idx].adj.size() == 0)
        {
            int assign_idx = -1;
            int assign_window_idx = -1;
            int min_cost;
            int begin_point = machines[machine_idx].window_id; // ��ʼ��
            for(auto window_id_ab : machines[machine_idx].Access_window)
            {
                int j = begin_point;
                // ����ҵ���ɷ��䴰�ھ���idһ�µ����id
                while(window_link[j] != window_id_ab && j < window_link.size()-1) j++;
                if(window_link[j] != window_id_ab) // ����������id�ں���û���ҵ������������id
                    continue;
                // �������ҵ���С�ɱ�������
                // ͨ�����ڲ�������
                int group_id = windows[window_id_ab].group_id; //��Ӧ���ڶ�Ӧ�ĳ���id
                // ������������
                for(auto idx_workshop : order_workshop)
                {
                    if((workshops[idx_workshop].group == group_id) &&
                    ((map_Machine_Power[machines[machine_idx].type][0] == workshops[idx_workshop].power_type) ||
                    (map_Machine_Power[machines[machine_idx].type][1] == workshops[idx_workshop].power_type)))
                    { 
                        int current_cost = machines[machine_idx].cost[workshops[idx_workshop].power_type];
                        if(assign_idx == -1 || current_cost < min_cost)
                        {
                            min_cost = current_cost;
                            assign_idx = idx_workshop;
                            assign_window_idx = j;
                        }
                    }
                }
            }
            machines[machine_idx].window_id = assign_window_idx;
            machines[machine_idx].workshop_id = assign_idx;
            continue;
        }
        // �ҵ��ýڵ����еĺ������ҵ���С�Ĵ���id��ֻ����������ϵ
        int min_idx = window_link.size()+1;
        for(auto next_idx : machines[machine_idx].adj)
        {
            if(machines[next_idx].window_id < min_idx)
            {
				min_idx = machines[next_idx].window_id;
            }
        }
        // �ڿɷ��䴰�ھ���id���ҵ����õ���Сid
        int assign_idx = -1;
        int assign_window_idx = -1;
        int min_cost;
        int begin_point = machines[machine_idx].window_id;
        for(auto window_id_ab : machines[machine_idx].Access_window)
        {
            // ����ҵ���ɷ��䴰�ھ���idһ�µ����id
            int j = begin_point;
            while(window_link[j] != window_id_ab && j < min_idx-2) j++;
            if(window_link[j] != window_id_ab) // ����������id�ں���û���ҵ������������id
			    continue;
                // �������ҵ���С�ɱ�������
                // ͨ�����ڲ�������
            int group_id = windows[window_id_ab].group_id; //��Ӧ���ڶ�Ӧ�ĳ���id
            // ������������
            for(auto idx_workshop : order_workshop)
            {
                if((workshops[idx_workshop].group == group_id) &&
                ((map_Machine_Power[machines[machine_idx].type][0] == workshops[idx_workshop].power_type) ||
                (map_Machine_Power[machines[machine_idx].type][1] == workshops[idx_workshop].power_type)))
                { 
                    int current_cost = machines[machine_idx].cost[workshops[idx_workshop].power_type];
                    if(assign_idx == -1 || current_cost < min_cost)
                    {
                        min_cost = current_cost;
                        assign_idx = idx_workshop;
                        assign_window_idx = j;
                    }
                }
            }
        }
        machines[machine_idx].window_id = assign_window_idx;
        machines[machine_idx].workshop_id = assign_idx;
    }

        

    for(auto machine_idx : log_g)
    {
        machines[machine_idx].window_id = window_link[machines[machine_idx].window_id];
    }

    for(auto machine_idx : log_g)
    {
        // ͨ�����ڲ�������
        int group_id = windows[machines[machine_idx].window_id].group_id; //��Ӧ���ڶ�Ӧ�ĳ���id
        // ������������
        int assign_idx = -1;
        int min_cost;
        for(auto idx : order_workshop)
        {
            if((workshops[idx].group == group_id) &&
            ((map_Machine_Power[machines[machine_idx].type][0] == workshops[idx].power_type) ||
            (map_Machine_Power[machines[machine_idx].type][1] == workshops[idx].power_type)))
            { 
                int current_cost = machines[machine_idx].cost[workshops[idx].power_type];
                machines[machine_idx].Access_workshop.push_back(idx);
                if(assign_idx == -1)
                {
                    assign_idx = idx;
                    min_cost = machines[machine_idx].cost[workshops[idx].power_type];
                    continue;
                }
                if(current_cost < min_cost)
                {
                    min_cost = current_cost;
                    assign_idx = idx;
                }
            }
        }
        machines[machine_idx].workshop_id = assign_idx;
        machines[machine_idx].assign = true;
    }

    // �������ṹ���к�����ˮ����������С����
   // cout<<"���������䷽��"<<endl;
    vector<Uint> machi_zone; vector<Uint> machi_win;
    for(int idx = 0 ; idx < Inp.MachiNum ; idx++)
        if(machines[idx].assign){
           // cout<<machines[idx].workshop_id<<' ';
            machi_zone.push_back(machines[idx].workshop_id);}
    //cout<<endl;
   /// cout<<"���������ˮ�ߴ��ڷ���"<<endl;
   // �������
       // ������ˮ��
    list<int> core_workflows;
    for(int i=0; i<Inp.CoreStreamIndex.size(); i++)
        core_workflows.push_back(Inp.CoreStreamIndex[i]);
	    vector<int> core_stream_machine;
    for(auto cwf : core_workflows) // ����������ˮ��
    {
        core_stream_machine.push_back(workflows[cwf].prev);
        core_stream_machine.push_back(workflows[cwf].next);
    }

    int pos = 1;
    while(pos != core_stream_machine.size()-1)
    {
        int pos_inner = pos+1;
        while(true)
        {
            if(core_stream_machine[pos_inner] == core_stream_machine[pos] || core_stream_machine[pos_inner+1] == core_stream_machine[0])
                break;
            pos_inner += 2;
        }
        int temp_m_idx_prev = core_stream_machine[pos_inner], temp_m_idx_next = core_stream_machine[pos_inner+1];
        if(core_stream_machine[pos_inner] == core_stream_machine[pos])
        {
            for(int idx = pos_inner+1 ; idx > pos+2 ; idx--)
                core_stream_machine[idx] = core_stream_machine[idx-2];
            core_stream_machine[pos+1] = temp_m_idx_prev, core_stream_machine[pos+2] = temp_m_idx_next;
        }
        else
        {
            for(int idx = pos_inner+1 ; idx > 1 ; idx--)
                core_stream_machine[idx] = core_stream_machine[idx-2];
            core_stream_machine[0] = temp_m_idx_prev, core_stream_machine[1] = temp_m_idx_next;
        }
        pos += 2;
    }
    vector<int> order_core_stream_machine;
    for(int idx = 0 ; idx < core_stream_machine.size() ; idx += 2)
        order_core_stream_machine.push_back(core_stream_machine[idx]);
    order_core_stream_machine.push_back(core_stream_machine[core_stream_machine.size()-1]);
    for(auto num : order_core_stream_machine)
        machi_win.push_back(machines[num].window_id);




//HJH 0513
/************************************************************************************************/

        
    Inp.CoreMachi = Creat_CoreMachi(Inp.CoreStreamIndex);
    vector<Uint> Machi_WinTemp;
    for(int i=0;i<Inp.MachiNum;i++)  Machi_WinTemp.push_back(machines[i].window_id);
    //for(auto n:Machi_WinTemp) cout<<n<<' ';cout<<endl;
    vector<Uint> Machi_WinIndex_temp = machi_win;
    vector<Uint> Machi_ZoneIndex_temp = MachitoZone(Machi_WinTemp, Machi_WinIndex_temp);

    //for(auto n:Machi_ZoneIndex_temp) cout<<n<<' '; cout<<endl;
    //for(auto n:Machi_WinIndex_temp) cout<<n<<' '; cout<<endl;

    cout<<Inp.MachiNum<<endl;
     for(auto mz:Machi_ZoneIndex_temp) cout<<mz<<' ';cout<<endl;
     cout<<Outp.CoreStepNum<<endl;
     for(auto mw:Machi_WinIndex_temp) cout<<mw<<' ';cout<<endl;


    //cout<<"TotalFree:"<<scost;cout<<endl;
    return 0;
}

