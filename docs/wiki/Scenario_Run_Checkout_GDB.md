
# Scenario - Sample Debug with GDB

This scenario demonstrates how to launch the **sample simulator** and its **checkout application** with **GDB** for debugging inside the NOS3 environment.  
It builds on the standard sample simulation scenario and integrates `gdb` into the launch process to allow real-time inspection, breakpointing, and step-through debugging of the `sample_checkout` application.

This is useful for:
* Debugging the sample payload logic
* Inspecting memory or variable values during runtime
* Tracing faults or validating application behavior

This scenario was last updated on 5/7/25 and leveraged the `dev` branch at the time [1209324].

## Learning Goals

By the end of this scenario, you should be able to:

* Launch the sample checkout application within a `gdb` session inside Docker
* Set breakpoints and run the application interactively
* Inspect variables and function call flow at runtime
* Integrate low-level debugging into a NOS3 simulation workflow

## Prerequisites

Before running the scenario, ensure the following steps are completed:
* [Getting Started](./Getting_Started.md)
  * [Installation](./Getting_Started.md#installation)
  * [Running](./Getting_Started.md#running)
* You are working from the top level of the NOS3 repository

---

## Walkthrough

### Step 1: Build NOS3

```bash
make
```

---
### Step 2: Build the Sample Checkout App

```bash
./scripts/checkout.sh
make stop
make debug
cd components/sample/fsw/standalone/
mkdir build
cd build
cmake .. -DTGTNAME=cpu1
make
exit
```

---
### Step 3: Edit the checkout script

We want the checkout script to launch the sample simulator.
We also want it to launch the sample checkout app under GDB.
Edit `./scripts/checkout.sh` as follows:
- Uncomment lines 164 (sample sim) and 165 (sample checkout)
- Insert `gdb` on line 165 between "$DBOX" and "./components/sample/fsw/standalone/build/sample_checkout"

### Step 4: Launch the Sample Sim and launch the Sample Checkout App in GDB

Open a new terminal and run the following `gnome-terminal` command:

```bash
./scripts/checkout.sh
```

**Note:** This assumes your environment variables (e.g., `$DFLAGS`, `$BASE_DIR`, `$SC_NUM`, `$DBOX`, `$SC_NETNAME`) are set as in a typical NOS3 session.
This should be done by the `checkout.sh` script.

---
### Step 5: Use GDB

Once inside the GDB session, you can:

* Set breakpoints:
  ```gdb
  break main
  ```
* Run the application:
  ```gdb
  run
  ```
* Step through code:
  ```gdb
  next
  step
  ```
* Inspect variables:
  ```gdb
  print variable_name
  info locals
  ```

To quit GDB and exit the Sample Simulator, NOS Engine, etc.:
```gdb
quit
make stop
```

---
### Optional: Enable TUI Mode

If your container supports `ncurses`, you can add `-tui` to enable the GDB text-based UI:

```bash
gdb -tui ./components/sample/fsw/standalone/build/sample_checkout
```

---
### Conclusion

You have now successfully launched a NOS3 sample component with `gdb` attached, allowing real-time interactive debugging. This is a powerful way to test payload logic and simulate edge cases directly inside your NOS3 development loop.
