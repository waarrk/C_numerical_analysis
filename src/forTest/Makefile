cc := bcc32c
objdir := obj
outdir := out

libs := $(wildcard lib/*.c)
srcs := $(wildcard *.c)
objs := $(wildcard obj/*.exe)
data := $(wildcard data/*.csv)


all: 12_1 12_2 34_1 34_2 56_1 56_2 78_1 78_2 910_1 910_2 1112_1 1112_2

test: 12_1_test 12_2_test 34_1_test 34_2_test 56_1_test 56_2_test 78_1_test 78_2_test 910_1_test 910_2_test 1112_1_test 1112_2_test

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

56_1: $(srcs) $(libs)
		$(cc) 56_1_LU_decomposition.c $(libs) -o $(objdir)\56_1_LU_decomposition.exe

56_2: $(srcs) $(libs)
		$(cc) 56_2_iterative_method.c $(libs) -o $(objdir)\56_2_iterative_method.exe

78_1: $(srcs) $(libs)
		$(cc) 78_1_eigenvalue.c $(libs) -o $(objdir)\78_1_eigenvalue.exe

78_2: $(srcs) $(libs)
		$(cc) 78_2_least_squares_approximation.c $(libs) -o $(objdir)\78_2_least_squares_approximation.exe

910_1: $(srcs) $(libs)
		$(cc) 910_1_complement.c $(libs) -o $(objdir)\910_1_complement.exe

910_2: $(srcs) $(libs)
		$(cc) 910_2_trapezoid_formula.c $(libs) -o $(objdir)\910_2_trapezoid_formula.exe

1112_1: $(srcs) $(libs)
		$(cc) 1112_1_romberg.c $(libs) -o $(objdir)\1112_1_romberg.exe

1112_2: $(srcs) $(libs)
		$(cc) 1112_2_euler_method.c $(libs) -o $(objdir)\1112_2_euler_method.exe

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

56_1_test: $(objs) $(data)
		$(objdir)\56_1_LU_decomposition.exe data\k5-input1.csv data\k5-input2.csv > $(outdir)\56_1_check.txt
		$(objdir)\56_1_LU_decomposition.exe data\k5-input1_test.csv data\k5-input2_test.csv > $(outdir)\56_1_test.txt

56_2_test: $(objs) $(data)
		$(objdir)\56_2_iterative_method.exe data\k6-input1.csv data\k6-input2.csv > $(outdir)\56_2_check.txt
		$(objdir)\56_2_iterative_method.exe data\k6-input1_test.csv data\k6-input2_test.csv > $(outdir)\56_2_test.txt

78_1_test: $(objs) $(data)
		$(objdir)\78_1_eigenvalue.exe data\k7-input.csv > $(outdir)\78_1_check.txt
		$(objdir)\78_1_eigenvalue.exe data\k7-input_test.csv > $(outdir)\78_1_test.txt

78_2_test: $(objs) $(data)
		$(objdir)\78_2_least_squares_approximation.exe data\k8-input.csv > $(outdir)\78_2_check.txt
		$(objdir)\78_2_least_squares_approximation.exe data\k8-input_test.csv > $(outdir)\78_2_test.txt

910_1_test: $(objs) $(data)
		$(objdir)\910_1_complement.exe data\k9-input.csv 2.0 > $(outdir)\910_1_check.txt
		$(objdir)\910_1_complement.exe data\k9-input_test.csv 2.0 > $(outdir)\910_1_test.txt

910_2_test: $(objs) $(data)
		$(objdir)\910_2_trapezoid_formula.exe data\k10-input.csv > $(outdir)\910_2_check.txt
		$(objdir)\910_2_trapezoid_formula.exe data\k10-input_test.csv > $(outdir)\910_2_test.txt

1112_1_test: $(objs) $(data)
		$(objdir)\1112_1_romberg.exe data\k11-input.csv 5 > $(outdir)\1112_1_check.txt
		$(objdir)\1112_1_romberg.exe data\k11-input_test.csv 5 > $(outdir)\1112_1_test.txt

1112_2_test: $(objs) $(data)
		$(objdir)\1112_2_euler_method.exe data\k12-input.csv > $(outdir)\1112_2_check.txt
		$(objdir)\1112_2_euler_method.exe data\k12-input_test.csv > $(outdir)\1112_2_test.txt