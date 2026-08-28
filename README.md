# Flank

Flank is a a modern, open-source SSRS designed for rapid iteration in an AI-world.

- 🔥 **Blazing-fast authoring loop** — No drag-and-drop. Just write SQL.
- 🤖 **AI-ready** — No bolted-on chatbot. Just use your favorite AI.
- 📦 **Cross-platform** — No Windows Server required. Just install and run.

[Install .exe](https://github.com/btf-org/flank/raw/refs/heads/windows/Output/FlankSetup.exe)

## Getting Started

<details>
<summary>Windows (EXE)</summary>

----

Right now, Windows is supported through WSL2 (see below). If you're interested in an EXE, please [let me know here](https://docs.google.com/forms/d/e/1FAIpQLSd_Il0SMnKwX06OPkX9JqRdPNRDOn0Jt11ChfPj4voWxiEn-Q/viewform?usp=publish-editor).

----

</details>

<details>
<summary>Windows (WSL2)</summary>

----

### 1. Install WSL / Ubuntu from PowerShell

Run PowerShell as Administrator (right-click on **PowerShell** > Run as administrator), run the following command, and restart Windows if prompted.

```powershell
wsl --install
```

### 2. Install prerequisites (`sqlcmd`)

In Ubuntu, run:

```bash
curl -fsSL https://raw.githubusercontent.com/btf-org/flank/refs/heads/main/build/install-scripts/sqlcmd.sh | sudo bash
```

### 3. If SQL Server is running locally on Windows, configure it for WSL

> If SQL Server is running on another server, skip to step 4

WSL runs in a separate network environment from Windows. We need to enable TCP and a couple other settings on SQL Server and then make sure it's reachable from WSL.

#### 3a. Enable TCP/IP

1. Open **SQL Server Configuration Manager** in Windows.
2. Go to: **SQL Server Network Configuration → Protocols for `<your instance>`**
3. Enable **TCP/IP**.
4. Open **TCP/IP → Properties → IP Addresses**, scroll to `IPAll`, clear `TCP Dynamic Ports`, and set `TCP Port` to `1433`.

#### 3b. Enable SQL Server Authentication

1. Open **SQL Server Management Studio (SSMS)**.
2. Right-click your server and go to: **Properties → Security**
3. Select: **SQL Server and Windows Authentication mode**
4. Click **OK**

You'll also need a SQL Server login that has access to the database you want to use with Flank.

#### 3c. Restart SQL Server

1. Open **SQL Server Configuration Manager**
2. Click "SQL Server Services" on the left
3. Right-click your server, click "Restart"
   
#### 3d. Create a SQL Server login

We'll create a SQL login named `flankuser` that Flank can use to connect to your database.

Replace `<your-database>` with the database you want to use with Flank, and run the following in SSMS:

```sql
USE master;
GO

CREATE LOGIN flankuser
WITH PASSWORD = 'FlankTest123!';
GO

USE <your-database>;
GO

CREATE USER flankuser FOR LOGIN flankuser;
GRANT SELECT TO flankuser;
GRANT EXECUTE TO flankuser;
GO
```

#### 3e. Allow SQL Server through Windows Firewall

Open PowerShell as Administrator and run:

```powershell
New-NetFirewallRule -DisplayName "SQL Server for WSL" -Direction Inbound -Protocol TCP -LocalPort 1433 -Action Allow
```

#### 3f. Find your Windows host IP

From WSL/Ubuntu, run:

```bash
ip route | awk '/default/ {print $3}'
```

This should return an IP address like:

```text
192.168.160.1
```

You'll use this address as the SQL Server host when you plug in your credentials to Flank.

#### 3g. Test the connection from WSL

From WSL, run:

```bash
sqlcmd -S <windows-ip>,1433 -d <your-database> -U flankuser -P 'FlankTest123!' -Q "SELECT 1"
```

Replace <windows-ip> with the IP address from step 3f and <your-database> with your database name. If you already had a login, replace `flankuser` and `FlankTest123!` as well.

If you get a result back, WSL can connect to your local SQL Server.

### 4. Install / Run Flank

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.101/flank_0.1.101_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.101_amd64.deb
```

### 5. Open Flank in a browser

Open this in your Windows browser: http://localhost:8083

### 6. Create a report

Click on `Import SPROC` or `Import query`, add your DB credentials, and follow the instructions.

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
wget https://github.com/btf-org/flank/releases/download/v0.1.101/flank_0.1.101_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.101_amd64.deb
```

### 3. Open Flank in a browser

Flank runs on port 8083 by default, so if you're running an Ubuntu desktop, open http://localhost:8083. If it's a cloud VM, it'll be `http://<public-ip>:8083`. And if it's a local VM, it'll be http://localhost:8083 or `http://<vm-ip>:8083` depending on your port settings (you can get the VM IP via by running `hostname -I` in the VM).

### 4. Create a report

Click on `Import SPROC` or `Import query`, add your DB credentials, and follow the instructions.

----

</details>

## Troubleshooting

<details>
  
<summary>Windows (WSL2)</summary>

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
