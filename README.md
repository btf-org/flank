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

#### 1. Install / Run

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.84/flank_0.1.84_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.84_amd64.deb
```

#### 2. Open Flank in a browser

It will be served on port 8083 (localhost:8083 if local, <cloud-ip>:8083 if on a cloud VM)

#### 3. Create a report from a SPROC

Look for `Import SPROC` on the bottom bar and click it. (This assumes you've already got a database set up with a SPROC you'd like to share)

----

</details>

