
#include <iostream>
#include <map>
#include <set>
using std::set;
#include <string>
using std::string;
#include <utility>
#include <vector>
#include <fstream>
using std::ifstream;
#include <sstream>
using std::ostringstream; using std::istringstream;
#include<stdexcept>
using std::domain_error; using std::invalid_argument;
#include<algorithm>
using std::set_symmetric_difference; using std::sort;

#include "proj07_functions.h";

using ServerData = std::map<std::string, std::set<std::string>>;

using UserName = const std::string &;
using ServerName = const std::string &;

/*
    search through server data for server name - if doesn't exist create new 
    entry and add username to that set - if exists add un to set - if already
    added return FALSE
*/
bool AddConnection(ServerData &sd, ServerName sn, UserName un)
{
    auto it = sd.find(sn);
    if (it != sd.end())
    {
        //if un in set
        auto ut = sd[sn].count(un);
        
        if(ut == 1)
        {
            return false;
        }
        else
        {
          sd[sn].insert(un); 
            
            return true;
        }
    }
    else
    {
        sd[sn].insert(un);
        return true;
    }
}

/*
    if name present - delete it
*/

bool DeleteConnection(ServerData &sd, ServerName sn, UserName un)
{
    auto ut = sd[sn].count(un);
    if(ut == 1)
    {
        sd[sn].erase(un);
        return true;
    }
    else    
    {
        return false;
    }
}

/*
    iterate through lines of file using whitespace
    to seperate into components - follow 
    second data piece's directions and call corresponding
    function
*/

ServerData ParseServerData(const std::string &fname)
{
    std::string user_name, command, server_name;

    std::string line;
    ifstream infile(fname);
    
    ServerData sd;
    if(infile)
    {
        while(getline(infile, line))
        {
            
            std::string entry = line;
            istringstream iss;
            iss.str(line);
            iss >> user_name;
            iss >> command;
            iss >> server_name;
            
            if (command == "join")
            {
                AddConnection(sd, server_name, user_name);
            }
            else if (command == "leave")
            {
                DeleteConnection(sd, server_name, user_name);
            }
            else
            {
                throw domain_error("domain_error");
            }
            
        }
    }
    return sd;
}


/*
    iterate through map and iterate through each set
*/

void PrintAll(std::ostream &out, const ServerData &sd)
{
    for(auto it = sd.begin(); it != sd.end(); ++it)
    {
        //std::cout << it->first << ":";
        out << it->first << " :";
        
        auto current_set = it->second;
        
        for(auto it = current_set.begin(); it != current_set.end(); ++it)
        {
            auto item = *it;
            out << " " << item;
        }
        
        out << "\n";
    }
    
}

/*
    iterate through map keeping track of key names
*/
set<string> AllServers(const ServerData &sd)
{
    set<string> all_serve;
    ostringstream oss;
    
    for(auto it = sd.begin(); it != sd.end(); ++it)
    {
        //oss << it->first;
        //std::string result = oss.str();
        all_serve.insert(it->first);
        //oss.clear();
    }
    return all_serve;
}


/*
    iterate through servers and all users 

*/
set<string> AllUsers(const ServerData &sd)
{
    set<string> all_users;
    
    for(auto it = sd.begin(); it != sd.end(); ++it)
    {
        auto current_set = it->second;
        
        for(auto it = current_set.begin(); it != current_set.end(); ++it)
        {
            auto item = *it;
            all_users.insert(item);
        }
        
    }
    return all_users;
}

/*
    iterate through servers testing presence of un 
*/

set<string> HasConnections(const ServerData &sd, UserName un)
{
    set<string> connections;
    
    for(auto it = sd.begin(); it != sd.end(); ++it)
    {
        
        auto first = string(it->first);
        
        auto current_set = it->second;
        auto ut = current_set.count(un);
        
        if(ut == 1)
        {
            connections.insert(first);
        }
    }
    return connections;
}

/*
    incomplete function
*/

void BalanceServers(ServerData &sd, ServerName sn1, ServerName sn2)
{
    //set 1
    set<string> current_set = sd[sn1];
    set<string> set_2 = sd[sn2];
    set<string> users_1;
    set<string> users_2;
    
    for(auto it = current_set.begin(); it != current_set.end(); ++it)
        {
            auto item = *it;
            users_1.insert(item);
        }
        
    for(auto it = set_2.begin(); it != set_2.end(); ++it)
        {
            auto item = *it;
            users_2.insert(item);
        }    
    
    set<string> c;
    set_symmetric_difference(users_1.begin(), users_1.end(), 
                         users_2.begin(), users_2.end(), std::inserter(c, c.begin()));
     
     
     
    /*                    
    long size = c.size();
    set<string> new_s1;
    set<string> new_s2;
    
    if (size % 2 == 0)
    {
        
        std::copy_n(c, (size/2), new_s1.begin() );
        std::copy_n(c, (size/2), new_s2.begin() );
        
        sd[sn1] = new_s1;
        sd[sn2] = new_s2;
    }
    //else
    //{
        
    //}
    */
}


/*
int main()
{
    ostringstream oss;
    ServerData sd;
    UserName u1="u1", u2="u2", u54 = "u54";
    ServerName s1="s1", s2="s2";
    //bool dele = DeleteConnection(sd,s1,u1);
   // std::cout <<result;
  //  bool result2 = AddConnection(sd,s1,u1);  
  //  std::cout << result2;
    auto server_data = ParseServerData("input.txt");
    PrintAll(oss, server_data);
    
    set<string> all_serve = AllServers(server_data);
    set<string> all_users = AllUsers(server_data);
    set<string> has_con = HasConnections(server_data, "loki");
    BalanceServers(server_data, "baron", "rusty");
    
}
*/
