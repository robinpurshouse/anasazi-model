#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --mem=2G
#SBATCH --job-name=anasazi_model
#SBATCH --output=anasazi_output
#SBATCH --time=00:06:00
#SBATCH --account=purshousemodule
#SBATCH --partition=acsehpc,sheffield

unset MODULEPATH
module use /usr/local/modulefiles/common/all/
module use /usr/local/modulefiles/staging/eb/all/
module load RepastHPC-Boost1.73.0/2.3.1-foss-2018b

make -j4
mpirun -n 1 --bind-to none ./bin/main.exe ./props/config.props ./props/model.props

