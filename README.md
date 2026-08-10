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

### 1. Install prerequisites (`sqlcmd`)

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

## Troubleshooting

### Installation failed

If the installation command fails, send me the **full terminal output**, including the command you ran.

---

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

Then try opening `http://\<vm-ip\>:8083` in Windows.

---

### Flank freezes when importing SPROCs

Check the Flank logs:

```bash
journalctl -u flank -n 100 --no-pager
```

Send me the output along with what you were trying to import.

---

### Flank freezes when running a SPROC

Check the Flank logs:

```bash
journalctl -u flank -n 100 --no-pager
```

Send me the output along with the SPROC you were trying to run and the parameters you entered.

---

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
