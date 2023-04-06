//#include "pugixml/pugixml.hpp"
#include "parse.hpp"
using namespace std;
using namespace pqxx;


int main(int argc, char *argv[])
{
  connection *C;
  try{
    C = new connection("dbname=EXCHANGE_SERVER user=postgres password=passw0rd");
    if (C->is_open()) {
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }
  //Load XML file
  //Test create request
  cout << "Create request test starting!!!" << endl;
  pugi::xml_document request_create_doc;
  pugi::xml_document response_create_doc;
  int creat_res;
  request_create_doc.load_file("test1.xml");
  creat_res = process_create(request_create_doc, response_create_doc,C);
  if(creat_res == 0)
    {
      response_create_doc.print(std::cout);
    }
  else
    {
      cout << "Create request fail." << endl;
      return -1;
    }
  cout << "Create request test end." << endl;
  /*
  //Test transaction request
  cout << "Transaction request test starting!!!" << endl;
  pugi::xml_document request_trans_doc;
  pugi::xml_document response_trans_doc;
  int trans_res;
  request_trans_doc.load_file("test2.xml");
  res = process_transaction(request_trans_doc, response_trans_doc,C);
  if(res == 0)
    {
      response_trans_doc.print(std::cout);
    }
  else
    {
      cout << "Transaction request fail." << endl;
      return -1;
    }
  cout << "Transaction request test end." << endl;
  */
  return 0;
}

/*
int main()
{
    // Load the XML file
    pugi::xml_document request_doc;
    request_doc.load_file("test2.xml");
    pugi::xml_node request_head = request_doc.child("transactions");
    //output xml
    pugi::xml_document response_doc;
    pugi::xml_node response_head = response_doc.append_child("results");

    string account_id = getAccount_ID(request_head);
  /////////Iterate through all the child node //////////
    for (pugi::xml_node child : request_doc.child("transactions")) 
    {
        if(to_string(child.name()) == "order")
        {
            std :: string sym = getSym(child);
            int amount = getAmount(child);
            double limit = getLimit(child);
            std :: string order = "  <opened sym=\""+to_string(sym)+"\" amount=\""+to_string(amount)+"\" limit=\"" 
            + to_string(static_cast<int>(limit))+"\" id=\""+to_string(123)+"\"/>\n";
            pugi::xml_parse_result order_node = response_head.append_buffer(order.c_str(), order.length());
        }
        else if(to_string(child.name()) == "query")
        {
            std :: string trans_id = getTrans_ID(child);
            std :: string query_open = "    <open shares= 10"+ to_string(10) +"/>\n";
            std :: string query_cancel = "    <canceled shares= 20"+to_string(20)+" time="+"tt"+"/>\n";
            std :: string query_execute = "    <executed shares= 30"+to_string(30)+" price="+to_string(1000)
                                            +" time="+"tt"+"/>\n";
            std :: string query_body = query_open + query_cancel + query_execute;
            std :: string query = "  <status id=\""+to_string(trans_id)+"\">\n" + query_body + "  </status>\n";
            pugi::xml_parse_result query_node = response_head.append_buffer(query.c_str(),query.length());
        }
        else if(to_string(child.name()) == "cancel")
        {
            std :: string trans_id = getTrans_ID(child);
            std :: string query_open = "    <open shares="+to_string(10)+"/>\n";
            std :: string query_cancel = "    <canceled shares="+to_string(20)+" time="+"tt"+"/>\n";
            std :: string query_execute = "    <executed shares="+to_string(30)+" price="+to_string(1000)
                                            +" time="+"tt"+"/>\n";
            std :: string query_body = query_open + query_cancel + query_execute;
            string canceled = "  <canceled id=\""+to_string(trans_id)+"\">\n" + query_body + "  </canceled>\n";
            pugi::xml_parse_result canceled_node = response_head.append_buffer(canceled.c_str(), canceled.length());
        }
        else
        {
            cout << "Illegal Tag in Transaction" << endl;
            return -1;
        }
    }
    response_doc.print(std::cout);
    return 0;
}
*/
/*
int main()
{
    // Load the XML file
    pugi::xml_document request_doc;
    request_doc.load_file("test1.xml");
    pugi::xml_node request_head = request_doc.child("create");
    //output xml
    pugi::xml_document response_doc;
    pugi::xml_node response_head = response_doc.append_child("results");

    // iterate through all the nodes under create
    for (pugi::xml_node child : request_head.children()) 
    {
        int account_id;
        string sym;
        float balance = 0.0;
        if(to_string(child.name()) == "account")
        {
            account_id = getAccount_ID(child);
            balance = getBalance(child);
            ///////Add new account to database////////
            //std :: string account = add_account(C,account_id, balance);
            std::string account = "  <created id=\""+to_string(account_id)+"\"/>\n";
            pugi::xml_parse_result account_node = response_head.append_buffer(account.c_str(), account.length());
        }
        else if(to_string(child.name()) == "symbol")
        {
            sym = getSym(child);
            for(pugi::xml_node acc: child.children())
            {
                int acc_id = getAccount_ID(acc);
                int amount = getNum(acc);
                //////Add stock to database//////
                //std :: string stock = add_stock(C, acc_id, sym, amount);
                std :: string stock = "  <created sym=\""+to_string(sym)+"\" id=\""+to_string(acc_id)+"\"/>\n";
                pugi::xml_parse_result stock_node = response_head.append_buffer(stock.c_str(), stock.length());
            }
        }
        else
        {
            cout << "Create tag is illegal." << endl;
            return -1;
        }
    }
    response_doc.print(std::cout);

    return 0;
}
*/
// Open an output file stream
//std::ofstream ofs("output.xml");

// Print the content of the XML document to the output file stream
//request_doc.print(std::cout);
//doc.print(ofs);
// Get the parent node where you want to add the new node
//pugi::xml_node parent = doc.child("people");

// Append the XML string as a child node of the parent node
//pugi::xml_node person = parent.append_buffer("<person name=\"John\" age=\"30\"/>");

// Save the modified XML back to the file
//doc.save_file("people.xml");
