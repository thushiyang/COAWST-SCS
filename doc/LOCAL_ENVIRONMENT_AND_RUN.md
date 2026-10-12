# Local Environment and Execution

## Source and version

- Official source: https://github.com/DOI-USGS/COAWST
- Training: https://github.com/DOI-USGS/COAWST/wiki/COAWST-Trainings
- Reference revision: `015bb31f138285d399d30b82f50332ce2b477203`.
- The local README identifies COAWST 3.8; the upstream README identified 3.9 when checked on 12 October 2026. Use the recorded revision for this configuration.
- Reference source: `/home/thushiyang/model/src/COAWST`.
- Reference case: `/home/thushiyang/model/projects/H1P2/CPL-0`.

These project-specific notes describe a GNU/WSL2 setup. Consult the documentation distributed with the selected revision for complete installation instructions.

## Package contents

The model archive is a tracked text-source subset, not a complete build distribution. Model data, binaries and compiled products are excluded. Obtain the full source at the recorded revision for compilation and retain component-specific licenses.

The CPL-0 archive contains scripts, headers, input configurations and smoke-test settings. It does not include executables, grids, boundary or initial conditions, atmospheric forcing, exchange weights or simulation outputs. Adapt absolute paths in a separate working copy. This migrated CPL-0 configuration is not a verified collection of all manuscript process-isolation cases.

## Reference environment

| Component | Version |
|---|---|
| Operating system | WSL2 Ubuntu 22.04.5 LTS |
| GNU Fortran | 11.4.0 |
| OpenMPI | 4.1.2 |
| NetCDF-C | 4.8.1 |
| NetCDF-Fortran | 4.5.4 |

MCT and compatible compiler, MPI and library paths are also required. Coupled grids may require SCRIP weights. Matching version numbers alone does not ensure binary compatibility. Conda can manage Python post-processing but does not replace the Fortran/MPI toolchain.

## Prepare source and dependencies

```bash
sudo apt update
sudo apt install build-essential gfortran cmake git perl csh tcsh m4 \
  openmpi-bin libopenmpi-dev libnetcdf-dev libnetcdff-dev netcdf-bin \
  libhdf5-dev libhdf5-openmpi-dev
mkdir -p ~/model/src ~/model/projects ~/model/runs ~/model/logs ~/model/envs
git clone https://github.com/DOI-USGS/COAWST.git ~/model/src/COAWST
git -C ~/model/src/COAWST checkout 015bb31f138285d399d30b82f50332ce2b477203
```

Build MCT following the selected revision's documentation. Configure GNU, MPI, NetCDF and MCT in the corresponding build scripts and compiler settings. The machine-specific `~/.bashrc_coawst` is not included; create your own validated environment configuration.

## Configure the case

1. Extract CPL-0 into a separate Linux project directory. Review `MY_ROOT_DIR`, `MY_PROJECT_DIR`, `MY_HEADER_DIR`, `MY_ANALYTICAL_DIR`, `BINDIR`, `SCRATCH_DIR`, MPI and library paths in the build scripts.
2. Review CPP options in `scs_couple.h` and analytical code in `ana_fsobc.h` and `ana_sediment.h`. Header changes require recompilation.
3. Check process allocation, model inputs and exchange weights in `coupling_scs.in`; ocean inputs and outputs in `scs_roms.in`; and wave grid, forcing, spectra and time range in `scs_swan.in`.
4. Supply excluded input data. Verify `VARNAME`, `GRDNAME`, `ININAME`, `BRYNAME`, `FRCNAME`, `SPOSNAM` and SCRIP paths against the intended event.
5. Direct outputs to a new run directory. Do not build in or overwrite the original project.

## Compile and execute

Validate the official Upwelling (ROMS) and Inlet_test Coupled (ROMS–SWAN) examples first. These commands assume paths and dependencies have been adapted:

```bash
cd ~/model/projects/H1P2/CPL-0
# Load your validated GNU/MPI/NetCDF/MCT environment.
bash ./build_coawst_H1P2_CPL0_wsl.sh -j 2
# Verify smoke-test paths, time range and separate output filenames.
mpirun -np 10 ./coawstM coupling_scs_smoke.in
# Run the full period after the smoke test and configuration review.
mpirun -np 10 ./coawstM coupling_scs.in
```

The reference configuration uses nine ROMS processes and one SWAN process. Adjust MPI allocation and ROMS decomposition for other configurations and available resources.

Check exit status, logs, time axes, valid wet cells, numerical ranges and coupling exchange. Inspect floating-point warnings and validate scientific results. Output files or completion messages alone are insufficient. Preparing this website did not install, compile or rerun the model.

## Working-copy policy

Treat original model, case and research files as read-only. Adapt copies in a separate workspace. Retain applicable licenses and cite COAWST and its components.
