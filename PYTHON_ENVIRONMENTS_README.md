# 🐍 Python Virtual Environments on Windows

> **Two approaches, one goal:** keep each project's Python and packages separate. Use either **Anaconda (Conda)** or Python 3's built-in **`venv`** for a project—not both at once.

| | Anaconda / Conda | Python 3 `venv` |
| --- | --- | --- |
| **Installed with** | Anaconda | Python 3 |
| **Manages** | Python versions, packages, and many non-Python dependencies | An isolated copy of an existing Python installation and its packages |
| **Package installer** | Primarily `conda` | `pip` |
| **Environment location** | Typically under Conda's environments directory | Usually `.venv/` inside the project |
| **Best for** | Data science or projects with complex dependencies | Lightweight, standard Python projects |

In the examples, `project-env` is an example Conda environment name, and `.venv` is an example directory. Replace `your_script.py` with your own file.

## 1. Anaconda (Conda)

Anaconda includes **Conda**, which creates isolated environments and installs packages. Open **Anaconda Prompt** to run the commands below. Create a separate environment instead of installing project dependencies into Conda's `base` environment.

### Everyday workflow

The commands below show a typical session, from creation through deactivation:

```bat
conda --version
conda create -n project-env python=3
conda activate project-env
python --version
conda install numpy pandas
conda list
python your_script.py
conda deactivate
```

To request a specific Python version, replace `python=3` with a version such as `python=3.12`.

### Inspect and manage environments

| Task | Command |
| --- | --- |
| List environments and their locations | `conda env list` |
| Show Conda settings and the active environment | `conda info` |
| Check the Python executable in the active environment | `python -c "import sys; print(sys.executable)"` |
| List packages in a named environment | `conda list -n project-env` |
| Install a package into the active environment | `conda install requests` |
| Remove a package from the active environment | `conda remove requests` |
| Switch to another environment | `conda activate other-env` |
| Delete an environment after deactivating it | `conda env remove -n project-env` |

### Save and recreate an environment

While `project-env` is active, save the explicitly requested Conda packages:

```bat
conda env export --from-history > environment.yml
```

Copy `environment.yml` to another Windows computer, or remove the original environment first. Then recreate and activate it:

```bat
conda env create -f environment.yml
conda activate project-env
```

`--from-history` keeps the file relatively portable but does **not** capture every automatically installed dependency or packages installed with `pip`. If you need a fuller snapshot of the current environment, use `conda env export > environment.yml` instead; a full export can contain platform-specific packages. Prefer `conda install` when possible. If a package is available only through pip, activate the environment, install Conda packages first, then run `python -m pip install package_name`.

## 2. Python 3's Built-in `venv`

`venv` comes with most Python 3 installations and creates a project-local environment. Open **PowerShell** or **Command Prompt**, navigate to your project directory, create `.venv`, and activate it with the commands for your shell. Its packages are installed with `pip`.

### Create and activate

**Windows — PowerShell**

```powershell
py -3 -m venv .venv
.\.venv\Scripts\Activate.ps1
```

**Windows — Command Prompt**

```bat
py -3 -m venv .venv
.venv\Scripts\activate.bat
```

To use a particular installed Python version, replace `py -3` with a selector such as `py -3.12` when creating the environment. An existing `venv` does not change Python versions when you upgrade your Python installation; recreate it if needed.

### Use, inspect, and leave the environment

Once activated, the following commands work in both PowerShell and Command Prompt:

```text
python --version
python -c "import sys; print(sys.executable)"
python -m pip install numpy pandas
python -m pip list
python -m pip show numpy
python your_script.py
python -m pip freeze > requirements.txt
deactivate
```

The Python executable shown by `sys.executable` should be inside `.venv`. After creating and activating a fresh environment, restore saved packages with `python -m pip install -r requirements.txt`. Use `python -m pip` instead of a standalone `pip` command to target the Python interpreter currently in use.

### Remove and recreate

Deactivate the environment first, then delete **only** its `.venv` directory. Create and activate a new one using the Windows commands above, then reinstall dependencies from `requirements.txt`.

| Shell | Delete `.venv` |
| --- | --- |
| Windows PowerShell | `Remove-Item -Recurse -Force .venv` |
| Windows Command Prompt | `rmdir /s /q .venv` |

## Good Habits

- Keep **one environment per project** and check `sys.executable` when unsure which Python is running.
- Do **not** commit `.venv/` to Git; add it to `.gitignore`. Share `requirements.txt` for `venv` or `environment.yml` for Conda.
- If `conda` is not recognized, use Anaconda Prompt or initialize Conda for your shell.
- If PowerShell blocks `Activate.ps1`, use Command Prompt or review your local PowerShell execution policy.
