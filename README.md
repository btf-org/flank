# Flank

> A modern, open-source SSRS

## Getting Started

<details>
<summary>Windows (WSL2)</summary>

----

## In Windows

### 1. Install WSL / Ubuntu from Powershell

Run PowerShell as Administrator (right click on **Powershell** > Run as administrator)Run the following command

```powershell
wsl --install
```

Restart Windows if prompted, and **open Ubuntu** to finish the setup.

<details>
  <summary><h3>2. If your DB is running locally, expose to WSL</h3></summary>

  
</details>

----

## In Ubuntu

### 1. Install prerequisites (`sqlcmd`)

From Ubuntu...

```bash
curl -fsSL https://raw.githubusercontent.com/btf-org/flank/refs/heads/main/build/install-scripts/sqlcmd.sh | sudo bash
```

### 2. Install / Run Flank

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.100/flank_0.1.100_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.100_amd64.deb
```

### 3. Open Flank in a browser

Open this in your Windows browser: http://localhost:8083

### 4. Create a report

Click on `Import SPROC` or `Import query`, add your DB credentials, and follow the instructions.

**If SQL Server is running on your Windows host** (as opposed to a remote/cloud machine) your normal login may not work from WSL. See the WSL troubleshooting section below.

----

</details>

<details>
<summary>Mac</summary>

----

### 1. Install prerequisites (`sqlcmd`)

```bash
brew install sqlcmd
```

### 2. Install / Run Flank

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank && sleep 2 && open http://localhost:8083
```

### 3. Open Flank in a browser

The above command should automatically open http://localhost:8083, but if it didn't, do that now.

### 4. Create a report

Click on `Import SPROC` or `Import query`, add your DB credentials, and follow the instructions.

----

</details>

<details>
  
<summary>Debian / Ubuntu</summary>

----

### 1. Install prerequisites (`sqlcmd`)

```bash
curl -fsSL https://raw.githubusercontent.com/btf-org/flank/refs/heads/main/build/install-scripts/sqlcmd.sh | sudo bash
```

### 2. Install / Run Flank

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.100/flank_0.1.100_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.100_amd64.deb
```

### 3. Open Flank in a browser

Flank runs on port 8083 by default.

**Note if running on a local VM:**
  - If your VM forwards localhost ports to Windows, open http://localhost:8083 in Windows
  - If not, run the following in your VM to get your VM's IP
    ```bash
    hostname -I
    ```
    Then open `http://<vm-ip>:8083`

### 4. Create a report

Click on `Import SPROC` or `Import query`, add your DB credentials, and follow the instructions.

----

</details>

## Troubleshooting

<details>

<summary>Mac</summary>

---

### Installation failed

If either installation command fails, send me the full terminal output, including the command you ran.

### Web page is blank (but not spinning)

Try refreshing the page. If that doesn't work, try the steps below.

### Web address spins and nothing happens

First, check whether Flank is responding:

```bash
curl http://localhost:8083
```

If that doesn't work, check whether Flank is running:

```bash
brew services list
```

If Flank is running but isn't responding, restart it:

```bash
brew services restart flank
```

If `curl http://localhost:8083` works, try opening http://localhost:8083 again in your browser.

### Flank hangs when importing SPROCs

First, make sure sqlcmd is installed:

```bash
sqlcmd --version
```

Then check that sqlcmd can connect to your database:

```bash
sqlcmd -S <server> -d <database> -U <username> -P '<password>' -Q "SELECT 1"
```

If that works, check the Flank logs:

```bash
tail -n 100 "$(brew --prefix)/var/log/flank/flankserver.log"
tail -n 100 "$(brew --prefix)/var/log/flank/flankserver.err"
```

Send me the output along with what you were trying to import.

### Flank hangs when running a SPROC

First, make sure sqlcmd can connect to your database:

```bash
sqlcmd -S <server> -d <database> -U <username> -P '<password>' -Q "SELECT 1"
```

If that works, try running the SPROC directly with sqlcmd:

```bash
sqlcmd -S <server> -d <database> -U <username> -P '<password>' -Q "EXEC <sproc>"
```

If the SPROC works with sqlcmd but hangs in Flank, check the Flank logs:

```bash
tail -n 100 "$(brew --prefix)/var/log/flank/flankserver.log"
tail -n 100 "$(brew --prefix)/var/log/flank/flankserver.err"
```

Send me the output along with the SPROC you were trying to run and the parameters you entered.

### Something else

This is an early build, so don't spend too long trying to debug unexpected behavior.

Send me:

* What you were trying to do
* What happened
* Any error message or screenshot
* The output of:

```bash
tail -n 100 "$(brew --prefix)/var/log/flank/flankserver.log"
tail -n 100 "$(brew --prefix)/var/log/flank/flankserver.err"
```

Thanks!

---

</details>

<details>
  
<summary>Debian / Ubuntu</summary>

----

### Installation failed

I've tested this Ubuntu 24.04. If the installation command fails, send me the full terminal output, including the command you ran.

### Web page is blank (but not spinning)

Try refreshing the page. If that doesn't work, try the steps below.

### Web address spins and nothing happens

First, check whether Flank is responding inside the Ubuntu VM:

```bash
curl http://localhost:8083
```

If that doesn't work, check whether Flank is running:

```bash
systemctl status flank
```

If Flank is running but isn't responding, restart it:

```bash
sudo systemctl restart flank
```

If `curl http://localhost:8083` **does work** and you're running Flank in a VM, Flank is running and the problem is likely the connection between Windows and your VM.

Get the VM's IP address:

```bash
hostname -I
```

Then try opening `http://<vm-ip>:8083` in Windows.


### Flank hangs when importing SPROCs

First, make sure sqlcmd is installed:

```bash
sqlcmd --version
```

Then check that sqlcmd can connect to your database:

```bash
sqlcmd -S <server> -d <database> -U <username> -P '<password>' -Q "SELECT 1"
```

If that works, check the Flank logs:

```bash
journalctl -u flank -n 100 --no-pager
```

Send me the output along with what you were trying to import.

### Flank hangs when running a SPROC

First, make sure sqlcmd can connect to your database:

```bash
sqlcmd -S <server> -d <database> -U <username> -P '<password>' -Q "SELECT 1"
```

If that works, try running the SPROC directly with sqlcmd:

```bash
sqlcmd -S <server> -d <database> -U <username> -P '<password>' -Q "EXEC <sproc>"
```

If the SPROC works with sqlcmd but hangs in Flank, check the Flank logs:

```bash
journalctl -u flank -n 100 --no-pager
```

Send me the output along with the SPROC you were trying to run and the parameters you entered.

### Something else

This is an early build, so don't spend too long trying to debug unexpected behavior.

Send me:

* What you were trying to do
* What happened
* Any error message or screenshot
* The output of:

```bash
journalctl -u flank -n 100 --no-pager
```

Thanks!

----

</details>
