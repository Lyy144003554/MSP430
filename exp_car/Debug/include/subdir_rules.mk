################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
include/%.obj: ../include/%.C $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS10.3.1.00003_win64/ccs/tools/compiler/ti-cgt-msp430_20.2.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/CCS10.3.1.00003_win64/ccs/ccs_base/msp430/include" --include_path="D:/ti/Worksplace/exp_car/include" --include_path="D:/CCS10.3.1.00003_win64/ccs/tools/compiler/ti-cgt-msp430_20.2.4.LTS/include" --advice:power=all -g --define=__MSP430F5229__ --display_error_number --diag_wrap=off --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="include/$(basename $(<F)).d_raw" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

include/%.obj: ../include/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS10.3.1.00003_win64/ccs/tools/compiler/ti-cgt-msp430_20.2.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/CCS10.3.1.00003_win64/ccs/ccs_base/msp430/include" --include_path="D:/ti/Worksplace/exp_car/include" --include_path="D:/CCS10.3.1.00003_win64/ccs/tools/compiler/ti-cgt-msp430_20.2.4.LTS/include" --advice:power=all -g --define=__MSP430F5229__ --display_error_number --diag_wrap=off --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="include/$(basename $(<F)).d_raw" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


