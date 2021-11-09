#pragma once
#include <iostream>
#include <mariadb/mysql.h>


class Database{

private:
    MYSQL* con;
    MYSQL_ROW row;
    MYSQL_RES* res;
    const char* server, *user, *password, *database;
    const char* sql_query = "";

public:

    Database(const char* s, const char* u, const char* p, const char* d) : server(s), user(u), password(p), database(d)
    {
        this->con = mysql_connection_setup();
    }
    
    ~Database(){
        // mysql_free_result(this->res);
        // mysql_close(this->con);
    }

private:


    MYSQL* mysql_connection_setup(){ 
    
        //link connection object as database initializer
        MYSQL * connection = mysql_init(NULL); 

        //attempt connection to database
        if(!mysql_real_connect(connection, this->server, this->user, this->password, this->database, 0, NULL, 0)){ 
            throw mysql_error(connection);
            
        }

        return connection;
    }  

    //attempt query
    MYSQL_RES* mysql_ex_query(MYSQL *connection, const char * sql_query){
    
        //returns true if error occurs
        if(mysql_query(connection, sql_query)){
            throw mysql_error(connection);
        }

        return mysql_store_result(connection);

    }

public:

    const char* setQuery(const char * sql_query){
        try{
            this->res = mysql_ex_query(con, sql_query);
        }catch(const char * sql_query){
            return "Error with submitted statement";
        }
        return sql_query;
        
    }

    MYSQL_RES* retrieveData(){
        return this->res;
    }

    static bool validate_database(const char* server, const char* user, const char* pass, const char* db){
        try{
            Database check(server, user, pass, db);
        }catch(...){
            return false;
        }
        return true;
    } 

#ifdef PR_DEBUG
    void* operator new(size_t size){
        std::cout << "Allocated Bytes: " << size << '\n';
        void * p = malloc(size);

        return p;
    }

    void operator delete(void * p, size_t size){
        std::cout << "Freed Bytes: " << size << '\n';
        free(p);
    }
#endif

    

};

