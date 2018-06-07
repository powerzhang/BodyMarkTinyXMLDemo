#include <iostream>
#include "TinyXml2/tinyxml2.h"
#include<assert.h>
#include<fstream>
#include"user.h"
using std::cout;
using std::endl;
using std::cerr;
using namespace std;
using namespace tinyxml2;

bool getXMLDeclaration(const char* xmlPath,string& strDecl);
int createXML(const char* xmlPath);
//int insertXMLNode(const char* xmlPath,const User& user);
XMLElement* queryUserNodeByName(XMLElement* root,const string& userName);
User* queryUserByName(const char* xmlPath,const string& userName);
bool updateUser(const char* xmlPath,User* user);
bool deleteUserByName(const char* xmlPath,const string& userName);

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    string strDecl;
    getXMLDeclaration("C:\\Users\\qustzj\\Desktop\\DBUSER.xml",strDecl);
    return 0;
}

//function:获取xml文件申明
//param:xmlPath:xml文件路径；strDecl：xml申明
//return：bool
bool getXMLDeclaration(const char* xmlPath,string& strDecl)
{

    XMLDocument doc;

    if(doc.LoadFile(xmlPath)!=0)
    {
        cout<<"load xml file failed"<<endl;
        return false;
    }
    XMLNode* decl=doc.FirstChild();
    if (NULL!=decl)
    {
        XMLDeclaration* declaration =decl->ToDeclaration();

        if (NULL!=declaration)
        {
              strDecl = declaration->Value();
              printf("strDecl : %s",strDecl.c_str());

              return true;
        }
    }
    return false;
}

//function：create a xml file
//param：xmlPath:xml文件路径
//return:0,成功，非0，失败
int createXML(const char* xmlPath)
{
    const char* declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
    XMLDocument doc;
    doc.Parse(declaration);//会覆盖xml所有内容

    //添加申明可以使用如下两行
    //XMLDeclaration* declaration=doc.NewDeclaration();
    //doc.InsertFirstChild(declaration);

    XMLElement* root=doc.NewElement("DBUSER");
    doc.InsertEndChild(root);

    return doc.SaveFile(xmlPath);
}

//function:insert XML node
//param:xmlPath:xml文件路径; user:用户对象
//return:0:成功; 非0:失败
//int insertXMLNode(const char* xmlPath,const User& user)
//{
//    XMLDocument doc;
//    int res=doc.LoadFile(xmlPath);
//    if(res!=0)
//    {
//        cout<<"load xml file failed"<<endl;
//        return res;
//    }
//    XMLElement* root=doc.RootElement();

//    XMLElement* userNode = doc.NewElement("User");
//    userNode->SetAttribute("Name",user.userName.c_str());
//    userNode->SetAttribute("Password ",user.password.c_str());
//    root->InsertEndChild(userNode);

//    XMLElement* gender = doc.NewElement("Gender");
//    XMLText* genderText=doc.NewText(itoa(user.gender));
//    gender->InsertEndChild(genderText);
//    userNode->InsertEndChild(gender);

//    XMLElement* mobile = doc.NewElement("Mobile");
//    mobile->InsertEndChild(doc.NewText(user.mobile.c_str()));
//    userNode->InsertEndChild(mobile);

//    XMLElement* email = doc.NewElement("Email");
//    email->InsertEndChild(doc.NewText(user.email.c_str()));
//    userNode->InsertEndChild(email);

//    return doc.SaveFile(xmlPath);
//}

//function:根据用户名获取用户节点
//param:root:xml文件根节点；userName：用户名
//return：用户节点
XMLElement* queryUserNodeByName(XMLElement* root,const string& userName)
{

    XMLElement* userNode=root->FirstChildElement("User");
    while(userNode!=NULL)
    {
        if(userNode->Attribute("Name")==userName)
            break;
        userNode=userNode->NextSiblingElement();//下一个兄弟节点
    }
    return userNode;
}

User* queryUserByName(const char* xmlPath,const string& userName)
{
    XMLDocument doc;
    if(doc.LoadFile(xmlPath)!=0)
    {
        cout<<"load xml file failed"<<endl;
        return NULL;
    }
    XMLElement* root=doc.RootElement();
    XMLElement* userNode=queryUserNodeByName(root,userName);

    if(userNode!=NULL)  //searched successfully
    {
        User* user=new User();
        user->userName=userName;
        user->password=userNode->Attribute("Password");
        XMLElement* genderNode=userNode->FirstChildElement("Gender");
        user->gender=atoi(genderNode->GetText());
        XMLElement* mobileNode=userNode->FirstChildElement("Mobile");
        user->mobile=mobileNode->GetText();
        XMLElement* emailNode=userNode->FirstChildElement("Email");
        user->email=emailNode->GetText();
        return user;
    }
    return NULL;
}
//function:修改指定节点内容
//param:xmlPath:xml文件路径；user：用户对象
//return：bool
//bool updateUser(const char* xmlPath,User* user)
//{
//    XMLDocument doc;
//    if(doc.LoadFile(xmlPath)!=0)
//    {
//        cout<<"load xml file failed"<<endl;
//        return false;
//    }
//    XMLElement* root=doc.RootElement();
//    XMLElement* userNode=queryUserNodeByName(root,user->userName);

//    if(userNode!=NULL)
//    {
//        if(user->password!=userNode->Attribute("Password"))
//        {
//            userNode->SetAttribute("Password",user->password.c_str());  //修改属性
//        }
//        XMLElement* genderNode=userNode->FirstChildElement("Gender");
//        if(user->gender!=atoi(genderNode->GetText()))
//        {
//            genderNode->SetText(itoa(user->gender).c_str());   //修改节点内容
//        }
//        XMLElement* mobileNode=userNode->FirstChildElement("Mobile");
//        if(user->mobile!=mobileNode->GetText())
//        {
//            mobileNode->SetText(user->mobile.c_str());
//        }
//        XMLElement* emailNode=userNode->FirstChildElement("Email");
//        if(user->email!=emailNode->GetText())
//        {
//            emailNode->SetText(user->email.c_str());
//        }
//        if(doc.SaveFile(xmlPath)==0)
//            return true;
//    }
//    return false;
//}
//function:删除指定节点内容
//param:xmlPath:xml文件路径；userName：用户名称
//return：bool
bool deleteUserByName(const char* xmlPath,const string& userName)
{
    XMLDocument doc;
    if(doc.LoadFile(xmlPath)!=0)
    {
        cout<<"load xml file failed"<<endl;
        return false;
    }
    XMLElement* root=doc.RootElement();
    //doc.DeleteNode(root);//删除xml所有节点
    XMLElement* userNode=queryUserNodeByName(root,userName);
    if(userNode!=NULL)
    {
        userNode->DeleteAttribute("Password");//删除属性
        XMLElement* emailNode=userNode->FirstChildElement("Email");
        userNode->DeleteChild(emailNode); //删除指定节点
        //userNode->DeleteChildren();//删除节点的所有孩子节点
        if(doc.SaveFile(xmlPath)==0)
            return true;
    }
    return false;
}
