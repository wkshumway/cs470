/***********************************************************************
* Program:
*    Example 3.2.3: ACL
* Author:
*    Br.  Helfrich
* Summary: 
*    This example is meant to demonstrate how to implement Linux style ACLs
*    in a simple system
************************************************************************/

#include <iostream>    // for CIN, COUT
#include <string>      // for STRING
#include <map>         // for VECTOR: a collection of Nodes
#include <cassert>     // because I am paranoid
using namespace std;

// SIDs
enum SID
{
   PUBLIC,
   GOD, CHUCK_NORRIS, BATMAN,
   DUMBLEDORE, HELFRICH, CITY_LA, PRESIDENT, PARENT, INTER_EXC, SYDNEY_OPERA,
   SUPER_HERO, LEADERS,
   NONE,
};

// mapping of user to SID
struct UserSID
{
   const char * username;
   SID    sid;
} const USER_SID[] =
{
   { "God",         GOD         },
   { "ChuckNorris", CHUCK_NORRIS},
   { "Batman",      BATMAN      },
   { "President",   PRESIDENT   },
   { "Br.Helfrich", HELFRICH    },
   { "Parent",      PARENT      },
   { "Dumbledore",  DUMBLEDORE  },
   { "CityLA",      CITY_LA     },
   { "InterExc",    INTER_EXC   },
   { "SydneyOpera", SYDNEY_OPERA }
};

#define MAX_GROUP 6

// mapping of user to group
struct GroupSID
{
   SID sidGroup;
   SID listMembers[MAX_GROUP];
} const GROUP_SID[] =
{
   { SUPER_HERO, {GOD, CHUCK_NORRIS, BATMAN, NONE, NONE, NONE}},
   { LEADERS,    {GOD, CHUCK_NORRIS, BATMAN, PRESIDENT, HELFRICH, PARENT}}
};

// ACE
struct ACE
{
   ACE() : sid(NONE), read(false), write(false) {}
   ACE(SID sid, bool read, bool write) :
         sid(sid), read(read), write(write) {}
   SID sid;
   bool read;
   bool write;
};

// ACL
struct ACL
{
   ACE owner;
   ACE group;
   ACE pub; // public is a keyword!
};


/*****************************************
 * NODE
 * One data item to be protected
 *****************************************/
struct Node
{
   string         data;      // the data that is protected
   ACL            acl;       // access permission
};

/*********************************************
 * ADDRESSES
 * A collection of addresses
 ********************************************/
class Addresses
{
public:
   // initialize the data
   Addresses();

   // display address list, this is not confidential information
   friend ostream & operator << (ostream & out, const Addresses & rhs)
   {
      map <string, Node> :: const_iterator it;
      for (it = rhs.addresses.begin(); it != rhs.addresses.end(); ++it)
         out << '\t' << it->first << endl;
      return out;
   }
   
   // fetch the address corresponding to key,
   //  there might be confidentialiy issues
   string get(const string & key,
              SID sidRequest) const;

   // change the address corresponding to key, there might be integrity issues
   void set(const string & key,
            const string & address,
            SID sidRequest);

private:

   // determine if we are legal
   bool securityCondition(const ACL & aclAsset,
                          const ACE & aceRequest) const;
   bool isMember(SID sidMember, SID sidGroup) const;
   map <string, Node> addresses;
};

/********************************************
 * ADDRESSES : constructor
 * Just fill our map with address data
 ********************************************/
Addresses :: Addresses()
{
   Node node;

   node.data = "Bronson Canyon, 3200 Canyon Dr., Los Angeles, CA 90068";
   node.acl.owner = ACE(BATMAN,     true,  true);
   node.acl.group = ACE(SUPER_HERO, true,  true);
   node.acl.pub   = ACE(NONE,       false, false);
   addresses[string("BatCave")] = node;   
   
   node.data = "platform 9 3/4, Kings Cross Station, London";
   node.acl.owner = ACE(DUMBLEDORE, true,  false);
   node.acl.group = ACE(SUPER_HERO, true,  true);
   node.acl.pub   = ACE(NONE,       false, false);
   addresses[string("Hogwarts")] = node;   

   node.data = "4059 Mt Lee Dr. Hollywood, CA 90068";
   node.acl.owner = ACE(CITY_LA,    true,  true);
   node.acl.group = ACE(SUPER_HERO, true,  true);
   node.acl.pub   = ACE(NONE,       true,  false);
   addresses[string("HollywoodSign")] = node;

   node.data = "626 Autumn Ct., Rexburg, ID";
   node.acl.owner = ACE(HELFRICH,   true,  true);
   node.acl.group = ACE(LEADERS,    true,  true);
   node.acl.pub   = ACE(NONE,       true,  false);
   addresses[string("Br.Helfrich")] = node;   

   node.data = "1600 Pennsylvania Avenue, Washington DC";
   node.acl.owner = ACE(PRESIDENT,  true,  false);
   node.acl.group = ACE(SUPER_HERO, true,  true);
   node.acl.pub   = ACE(NONE,       true,  false);
   addresses[string("WhiteHouse")] = node;

   node.data = "11 Wall Street, New York, NY";
   node.acl.owner = ACE(INTER_EXC,  true,  true);
   node.acl.group = ACE(LEADERS,    true,  true);
   node.acl.pub   = ACE(NONE,       false, false);
   addresses[string("NYSE")] = node;

   node.data = "2 Macquarie Street, Sydney";
   node.acl.owner = ACE(SYDNEY_OPERA,true,  true);
   node.acl.group = ACE(LEADERS,    true,  true);
   node.acl.pub   = ACE(NONE,       true, false);
   addresses[string("OperaHouse")] = node;
}

/***************************************************
 * ADDRESS :: IS MEMBER
 * Is a given SID a part of a given group?
 **************************************************/
bool Addresses :: isMember(SID sidMember, SID sidGroup) const
{
   for (int iGroup = 0;
        iGroup < sizeof(GROUP_SID) / sizeof(GROUP_SID[0]);
        iGroup++)
      if (GROUP_SID[iGroup].sidGroup == sidGroup)
      {
         for (int iMember = 0; iMember < MAX_GROUP; iMember++)
            if (GROUP_SID[iGroup].listMembers[iMember] == sidMember)
               return true; // Member SID is found. we are a member!
         return false; // Member SID not found in group
      }
   
   return false; // Group SID not found
}
     
/****************************************************
 * ADDRESSES :: SECURITY CONDITION
 * Does the entity have access to the asset?
 ****************************************************/
bool Addresses :: securityCondition(const ACL & aclAsset,
                                    const ACE & aceRequest) const
{
   // try owner first
   if (aceRequest.sid == aclAsset.owner.sid)
   {
      if (aceRequest.read)
         return aclAsset.owner.read;
      if (aceRequest.write)
         return aclAsset.owner.write;
      assert(false);  // we should never be here!
      return false;
   }

   // try group next
   if (isMember(aceRequest.sid, aclAsset.group.sid))
   {
      if (aceRequest.read)
         return aclAsset.group.read;
      if (aceRequest.write)
         return aclAsset.group.write;
      assert(false);  // we should never be here!
      return false;
   }

   // finally try public
   if (aceRequest.read)
      return aclAsset.pub.read;
   if (aceRequest.write)
      return aclAsset.pub.write;
   assert(false);  // we should never be here!
   return false;
}

/*********************************************
 * ADDRESSES :: GET
 * Fetch the address for a given location
 ********************************************/
string Addresses :: get(const string & key,
                        SID sidRequest) const
{
   // does the item exist?
   map <string, Node> :: const_iterator it = addresses.find(key);
   if (it == addresses.end())
      return string("Name not found");

   // protection by ACL
   ACE aceRequest(sidRequest, true, false);
   if (securityCondition(it->second.acl, aceRequest))
      return it->second.data;
   else
      return string("You don't have clearance for that!");
}

/***********************************************
 * ADDRESSES :: SET
 * change the address corresponding to key
 **********************************************/
void Addresses :: set(const string & key,
                      const string & address,
                      SID sidRequest)
{
   ACE aceRequest(sidRequest, false, true);

   // protected by Biba
   if (securityCondition(addresses[key].acl, aceRequest))
      addresses[key].data = address;
   else
      cout << "You do not have permission to make this change.\n";
}

/*********************************************
 * AUTHENTICATE
 ********************************************/
SID authenticate()
{
   string name;
   cout << "Name: ";
   cin  >> name;

   for (int i = 0; i < sizeof(USER_SID) / sizeof(USER_SID[0]); i++)
      if (name == string(USER_SID[i].username))
         return USER_SID[i].sid;

   return NONE;
}

/**********************************************************************
 * MAIN: Just a driver program to exercise our Bell-LaPadula access control
 ***********************************************************************/
int main()
{
   // fill up our secret data
   Addresses a;

   SID sidUser = authenticate();

   cout << "What address do you want?\n"
        << a;
   for (;;)
   {
      // select an item...
      string key;
      cout << "> ";
      cin  >> key;
      cin.ignore();

      // display the contents
      cout << '\t' << a.get(key, sidUser) << endl;

      // change the contents
      string data;
      cout << "  new data for " << key << ": ";
      getline(cin, data);
      if (data.size())
         a.set(key, data, sidUser);
   }
   
   
   return 0;
}
