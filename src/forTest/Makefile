cc := bcc32c
objdir := obj
outdir := out

libs := $(wildcard lib/*.c)
srcs := $(wildcard *.c)
objs := $(wildcard obj/*.exe)
data := $(wildcard data/*.csv)


all: 12_1 12_2 34_1 34_2

test: 12_1_test 12_2_test 34_1_test 34_2_test

clean:
		del $(objdir)\*.exe
		del $(objdir)\*.tds
		del $(outdir)\*.txt

12_1: $(srcs) $(libs)
		$(cc) 12_1_decimal2bin.c $(libs) -o $(objdir)\12_1_decimal2bin.exe

12_2: $(srcs) $(libs)
		$(cc) 12_2_matrixproduct.c $(libs) -o $(objdir)\12_2_matrixproduct.exe

34_1: $(srcs) $(libs)
		$(cc) 34_1_nonlinearequation.c $(libs) -o $(objdir)\34_1_nonlinearequation.exe

34_2: $(srcs) $(libs)
		$(cc) 34_2_gaussian_w_partialpivot.c $(libs) -o $(objdir)\34_2_gaussian_w_partialpivot.exe

12_1_test: $(objs) $(data)
		$(objdir)\12_1_decimal2bin.exe data\k1-input.csv > $(outdir)\12_1_check.txt
		$(objdir)\12_1_decimal2bin.exe data\k1-input_test.csv > $(outdir)\12_1_test.txt

12_2_test: $(objs) $(data)
		$(objdir)\12_2_matrixproduct.exe data\k2-input1.csv data\k2-input2.csv > $(outdir)\12_2_check.txt
		$(objdir)\12_2_matrixproduct.exe data\k2-input1_test.csv data\k2-input2_test.csv > $(outdir)\12_2_test.txt

34_1_test: $(objs) $(data)
		$(objdir)\34_1_nonlinearequation.exe data\k3-default.csv data\k3-input.csv > $(outdir)\34_1_check.txt
		$(objdir)\34_1_nonlinearequation.exe data\k3-default.csv data\k3-input1_test.csv > $(outdir)\34_1_test.txt

34_2_test: $(objs) $(data)
		$(objdir)\34_2_gaussian_w_partialpivot.exe data\k4-input1.csv data\k4-input2.csv > $(outdir)\34_2_check.txt
		$(objdir)\34_2_gaussian_w_partialpivot.exe data\k4-input1_test.csv data\k4-input2_test.csv > $(outdir)\34_2_test.txt