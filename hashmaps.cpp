

#include <iostream>
#include <typeinfo>
using namespace std ;

template<typename t , typename v>
class bucket
{
     public:
    t key;
    v value;

    bucket<t,v> * next;

    bucket ( t key , v value )
    {
      this -> key = key ;
      this -> value = value ;
    }
    ~bucket ()
    {
        //delete head
        delete next ;
    }

};
template<typename t , typename v >
class map
{
  bucket<t,v> ** arr;
  int  size;
  int capacity ;

 public:
  map ( )
  {
    capacity = 5;
    size = 0 ;
    arr = new bucket<t,v> * [capacity] ; 
    for ( int i=0; i<capacity; i++)
    {
      arr[i] = NULL;
    }

  }
  int hashfunction ( t key  )
  {
    
     //int index ;

    // if ( typeid(t) == typeid(string) )
    // {
        //abc
       int index = 0  ;
        int coef = 1 ;
        for ( int i = key.size() - 1 ; i >= 0 ; i-- )
        {
             index += key[i]*coef;
             index %= capacity;
             coef*=37;
             coef %= capacity;  // no problem dong so
        }
          return index % capacity ;

     //}

     /*
     else if ( typeid(t)== typeid(int) )
     {
           if (key < 0 )
           {
             index = -1 * key ;
           }
           else{
            index = key ;
           }
     }
     else if ( typeid(t)==typeid(char) )
     {
        index = int ( key ) ; // ascii value ;
     }
     */
       // compression
      // compression
  }
  void rehash ()
  {
   
   //isue of newcapacity compressiom

   bucket<t,v>** temp = arr ;


   int oldcapacity= capacity;

   capacity*=2;  // assign newcpaacity


  arr = new bucket<t,v> * [capacity];
  for ( int i=0; i<capacity; i++)
  {
    arr[i] = NULL;
  }

  size=0;

  for ( int i=0; i<oldcapacity; i++)
  {

     bucket<t,v>* head = temp[i];
     while ( head )
     {
      t key = head->key;
      v value = head->value;
      insert ( key , value );

      head = head -> next ;
     }
  }

// delete temp stored

   for ( int i=0; i<oldcapacity; i++)
   {
        delete temp[i];
   }
   delete[] temp ;

     

  }
  void insert ( t key , v value )  // seperate chaininig
  {
    int index = hashfunction ( key ) ;
    bucket<t,v> * head = arr[index] ;  // adress of that head of LL
    while ( head)
    {
      if ( head->key==key)
      {
         head->value=value;
          return; // dont increment size when update
      }
        head=head->next;
    }

    bucket<t,v> * node = new bucket<t,v> ( key , value);
    node -> next = arr[index] ;
    arr[index] = node ;
    size++ ;

    //cout << "\nkey :" << key << " and  " <<" val : " << value << " stored\n";

    // rehashing check 
   double loadfactor = (  1.0 *  size ) / capacity ;
   
    if ( loadfactor > 0.7 )
    {
      rehash () ;
    }
  }
  double getloadfactor ()
  {
    return  (  1.0 *  size ) / capacity ;
  }
  void remove ( t key  )
  {
     int index = hashfunction ( key );

     bucket<t,v> * head = arr[index];
     bucket<t,v>* prev = NULL;

    while ( head )
    { 
      if ( head->key==key)
      {
          if ( prev==NULL)
          {
            arr[index] = head->next;
          }
          else{
            prev->next = head->next;
          }
          head->next=NULL;
          delete head ;
          cout << "\n\nkey : " << key << " deleted \n\n" ;
          size--;
          return;
      }
      prev = head ;
      head = head -> next ;
    }
    cout <<"\n\nvaluenot found";
  }

  v getvalue ( t key  )
  {
      int index = hashfunction( key ) ;

      bucket<t , v> * head = arr [ index] ;

      while ( head )
      {
        if ( head->key==key)
        {
          return head -> value ;
        }
        head=head->next;
      }
      return 0;


  }

  int getsize ( )
  {
     return size;
  }



};


int  main (  )
{
   
  map<string , int > x ; 
  for ( int i=0; i<10; i++)
  {
    string ans = "abc";
    char c=i+'0';
    ans+=c;

    x.insert ( ans , i+1 );
    cout << x.getloadfactor() << endl;




  }

  
   cout <<"\n\nsize:" << x.getsize() << endl;


 

  
      
}