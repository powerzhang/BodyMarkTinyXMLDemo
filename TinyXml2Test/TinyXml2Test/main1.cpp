#include <iostream>
#include<vector>
#include "TinyXml2/tinyxml2.h"
#include "bodymarkdemo.h"
#include <iterator>
using namespace std;
using namespace tinyxml2;
void read(const char* filePath,vector<BodyMarkBean>& bodymarkBeanList);
void write(const char* filePath,vector<BodyMarkBean>& bodymarkBeanList);
int main(int argc, char *argv[])
{
  vector<BodyMarkBean> bodymarkBeanList1;
  const char* xmlPath = "C:\\Users\\qustzj\\Documents\\TinyXml2Test\\TinyXml2Test\\Body\ Mark\\ABD.xml";
  const char* savePath = "C:\\Users\\qustzj\\Documents\\TinyXml2Test\\TinyXml2Test\\Body\ Mark\\ABD1.xml";
  read(xmlPath,bodymarkBeanList1);

  printf("\nread finished Size:%d",bodymarkBeanList1.size());
  for(auto i = bodymarkBeanList1.begin(); i != bodymarkBeanList1.end();i++)
  {

      printf("\ntext : %s ,filename:%s,isDefault : %d,page : %d,row : %d,column : %d",
             i->text.c_str(),
             i->filename.c_str(),
             i->isDefault,
             i->page,
             i->row,
             i->column);

  }
   write(savePath,bodymarkBeanList1);
    return 0;
}
void write(const char* filePath,vector<BodyMarkBean>& bodymarkBeanList){
    XMLDocument doc;

    XMLElement* root = doc.NewElement( "preset" );
    doc.InsertEndChild( root );
    XMLElement* bodymarkElement = doc.NewElement( "bodymark" );

    for(BodyMarkBean bodyMarkBean : bodymarkBeanList){
        XMLElement* element = doc.NewElement( "element" );

        element->SetText(bodyMarkBean.text.c_str());
        element->SetAttribute("filename",bodyMarkBean.filename.c_str());
        element->SetAttribute("default",bodyMarkBean.isDefault);
        element->SetAttribute("page",bodyMarkBean.page);
        element->SetAttribute("row",bodyMarkBean.row);
        element->SetAttribute("column",bodyMarkBean.column);
        bodymarkElement->InsertEndChild(element);
    }

    root->InsertEndChild(bodymarkElement);
    XMLError xx = doc.SaveFile( filePath );
    printf("xx : %d",xx);
}
void read(const char* filePath,vector<BodyMarkBean> &bodymarkBeanList){

         XMLDocument doc;
         if(doc.LoadFile(filePath)!=0)
         {
             printf("%s","load xml file failed");
             return ;
         }

        XMLElement* preset = doc.RootElement();
        XMLElement *bodymark = preset->FirstChildElement("bodymark");
        printf("%s","load bodymark xml file success");
        XMLElement *element = bodymark->FirstChildElement("element");

        while(element){
            string text = element->GetText();
           const char* filename = element->Attribute("filename");
           bool isDefault = element->BoolAttribute("default");
           int page = element->IntAttribute("page");
           int row = element->IntAttribute("row");
           int column = element->IntAttribute("column");
//           printf("\ntext: %s,filename:%s,isDefault : %d,page : %d,row : %d,column : %d",
//                  text.c_str(),filename,isDefault,page,row,column);
            BodyMarkBean bodymarkbean;
            bodymarkbean.text = text;
            bodymarkbean.filename = filename;
            bodymarkbean.isDefault = isDefault;
            bodymarkbean.page = page;
            bodymarkbean.row = row;
            bodymarkbean.column = column;
            bodymarkBeanList.push_back(bodymarkbean);

            element = element->NextSiblingElement();
        }

}
