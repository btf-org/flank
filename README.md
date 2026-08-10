# Flank

> A modern, open-source SSRS

## Getting Started

<details>
<summary>Mac</summary>

----
  
#### 1. Install / Run

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && { nohup $(which flankserver) >> $(brew --prefix)/var/log/flank/flankserver.log 2>> $(brew --prefix)/var/log/flank/flankserver.err & } && sleep 1 && open http://localhost:8083
```

#### 2. Open Flank in a browser

The above command should automatically open http://localhost:8083, but if it didn't, do that now.

#### 3. Create a report from a SPROC

Look for `Import SPROC` on the bottom bar and click it. (This assumes you've already got a database set up with a SPROC you'd like to share)

----

</details>

<details>
  
<summary>Debian / Ubuntu</summary>

----

### 1. Install `sqlcmd`

```bash
curl -fsSL https://raw.githubusercontent.com/btf-org/flank/refs/tags/v0.1.89/build/install-scripts/sqlcmd.sh | sudo bash
```

### 2. Install / Run Flank

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.89/flank_0.1.89_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.89_amd64.deb
```

### 3. Open Flank in a browser

Flank runs on port 8083 by default.

**Note if running on a VM:**
  - If your VM forwards localhost ports to Windows, open http://localhost:8083 in Windows
  - If not, run the following in your VM to get your VM's IP
    ```bash
    hostname -I
    ```
    Then open http://\<vm-ip\>:8083

### 4. Create a report from a SPROC

Click on `Import SPROC` and follow the flow

----

</details>

## Troubleshooting

<details>
  
<summary>Debian / Ubuntu</summary>

----

### Flank isn't running

Check the service:

```bash
systemctl status flank
```

Restart it:

```bash
sudo systemctl restart flank
```

### I can't open Flank in my browser

First, check whether Flank is reachable inside the VM:

```bash
curl http://localhost:8083
```

If that works, Flank is running and the issue is probably networking
between your VM and Windows.

Get the VM's IP:

```bash
hostname -I
```

Then open:

```bash
http://<vm-ip>:8083
```


### Flank can't connect to SQL Server

Remember that the connection is being made from the Ubuntu VM, not
from Windows.

Test the connection directly:

```bash
sqlcmd -S <server> -U <username> -P '<password>' -Q "SELECT 1"
```

### Logs

```bash
journalctl -u flank -n 100 --no-pager
```

### Uninstall / Start Over

```bash
sudo apt remove flank
```

This will not remove any Flank data that you created in your session

### Still stuck?

Send me:

- What you were trying to do
- The output of:
```bash
journalctl -u flank -n 100 --no-pager
```

----

</details>
