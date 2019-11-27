Author:
-name: Josh Chisholm
-student number: 100770668

How run applipation:
Step 1) Decompress using the following command
tar -zxvf A1_JoshChisholm.tar.gz
Step 2) Open the app folder using the following command
cd app
Step 3) Build application using make file using the following command
make jtunes
Step 4) Run application using the following command
./jtunes
Step 4) If you want to run the testing in step 5, you must first clear the contents of the database (but keep the schema). Do this by using the following command
sqlite3 beatles.db < test_00_wipe_db.sql
Step 5) If desired, there are 4 testing files that can be run in the application by typing
.read test_01_add_populate.txt
.read test_02_add.txt
.read test_03_show.txt
.read test_04_delete.txt
Step 6) Use application and grade assignment (thank you!)
Note: "show" with no arguments is a invalid command and will display an error, but it will also show the breakdown of objects. This may be helpful for testing.
Step 7) Clean up folder using the following command (optional)
make clean
