# Database Systems Thomas Connolly & Carolyn Begg (6th Ed.)
## Chapter 1
[Database Systems](https://moodle.ucl.ac.uk/mod/resource/view.php?id=679623)
### File-Based Approach
* Definition: 
    A collection of application programs that perform services for the end-users, such as the production of reports. Each program defines and manages its own data.

* For instance: 
    an origansation might have physical files to hold all correspondence relating to a project
    Files :       task                  employee                  client, ...  
    For safety,   cabient(task)         cabinet(employee)         cabient(client)...  
    For security, locker(cabient(task)) locker(cabient(employee)) locker(cabient(client))...  
    lockers are located in somewhere secure in the building

* Indexing System
  E.g. have divisions in the filing system or seperate folders for different type of items that are in some way *logically related*

* Disadvantage
  It breaks down when we have to cross-reference or process the information in the files
  (Need numerous new files)

* Assistance 
  A decentralised approach was taken, for each department, with the assistance of __Data Processing__ (__DP__) staff, stored and controlled its own data.

  [File-Based Systems](https://player.slideplayer.com/24/7368418/data/images/img2.jpg)
  > Each department accessing their own files through application programs written especially for them.
  > The physical structure and storage of the data files andrecords are defined in the application code.

  > A file is simply a collection of __records__, which contains __logically related data__.

* Limitations of the File-Based Approach
    * Seperation & isolation of data
       * Difficult to access data that should be available
       * Developers must synchronize the processing of two fils to ensure the correct data is extracted
    * Duplication of data  
       * Owing to the decentralised approach  
       * Duplication is wasteful. It costs time and money to enter the data more than once.  
       * Takes up additional storage space, again with associated costs.   
       * May lead to loss of data integrity(i.e. inconsistency)   
        e.g. only inform one department, not the other, cause inconsistency  
    * (Program-)Data dependence  
       * Needs a one-off program to change the structure of a file  
       * All programs that access that file must be modified to conform to the new file structure   
    * Incompatiable file formats  
    * Fixed quiries / proliferation of application programs  