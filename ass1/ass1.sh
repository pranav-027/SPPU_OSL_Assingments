echo "Enter Name of Addressbook"
read fname
touch $fname
echo "Addressbook with name $fname Created Successfully"
echo -e "NAME \t ID \t DOB \t ADDRESS \t NUMBER \t SALARY" >> $fname
a=0
while [ $a -lt '7' ]
do
echo -e "ADDRESS BOOK : \n"
echo -e "1.CREATE ADDRESS BOOK"
echo -e "2.VIEW ADDRESS BOOK"
echo -e "3.INSERT NEW RECORD"
echo -e "4.DELETE A RECORD"
echo -e "5.MODIFY A RECORD"
echo -e "6.SEARCH A RECORD"
echo -e "7.EXIT FROM ADDRESS BOOK"
echo -e "ENTER YOUR CHOICE: "
read a
case $a in
1) echo -e "Enter number of records you want to enter \t"
read n
for((i=0;i<$n;i++))
do
echo -e "Enter Name of Employee\t"
read ename
echo -e "Enter ID of Employee\t"
read eid
echo -e "Enter DOB of Employee\t"
read edob
echo -e "Enter Address of Employee\t"
read eadd
echo -e "Enter Mobile of Employee\t"
read emob
echo -e "Enter salary of Employee\t"
read esal
echo -e "$ename \t $eid \t $edob \t $eadd \t $emob \t $esal \n">>$fname
done
;;
2)
cat $fname
;;
3)
echo -e "Enter New Record"
echo -e "Enter Name of Employee\t"
read ename
echo -e "Enter ID of Employee\t"
read eid
echo -e "Enter DOB of Employee\t"
read edob
echo -e "Enter Address of Employee\t"
read eadd
echo -e "Enter Mobile of Employee\t"
read emob
echo -e "Enter salary of Employee\t"
read esal
echo -e "$ename \t $eid \t $edob \t $eadd \t $emob \t $esal \n">>$fname
;;
4)
echo -e "Enter Employee ID to be Deleted"
read eid
if grep -w $eid $fname
then
grep -wv $eid $fname >>temp
rm $fname
mv temp $fname
echo "Record Deleted Successfully"
else
echo "Record does not exist"
fi
;;
5)
echo "Enter Employee ID to be Modified"
read eid
if grep -w $eid $fname
then
grep -wv $eid $fname >>temp
rm $fname
mv temp $fname
echo -e "Enter modified record"
echo -e "Enter Name of Employee\t"
read ename
echo -e "Enter ID of Employee\t"
read eid
echo -e "Enter DOB of Employee\t"
read edob
echo -e "Enter Address of Employee\t"
read eadd
echo -e "Enter Mobile of Employee\t"
read emob
echo -e "Enter salary of Employee\t"
read esal
echo -e "$ename \t $eid \t $edob \t $eadd \t $emob \t $esal \t">>$fname
else
echo "Record does not exist"
fi
;;
6)
echo -e "Enter Employee ID to be Searched"
read eid
if grep -w $eid $fname
then
grep -w "^$eid" $fname
echo "Record Found"
else
echo "Record does not exist"
fi
;;
esac
done