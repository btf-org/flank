# Flank

Flank is a 30-seconds-or-less software microwave for doing simple things quickly. 

## Quickstart - Scrape a website at 2 AM

1. Install Flank

    #### Mac
    ```bash
    brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank && open http://localhost:8083
    ```

    #### Linux / Ubuntu / apt
    ```
    wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
    ```

2. Go to the Flank website - http://localhost:8083
3. Click on `Create Cmd` on the bottom bar
4. Paste this into the box

    ```bash
   
    ```
5. Click on `Create Cron` on the bottom bar and paste in `0 2 * * *` into the `cron_expression`
6. Make sure your computer is on at 2 AM (for Mac users, check out Amphetamine)

## 30 seconds or less



Check out the list of things that should take 30 seconds or less:


- [R](/docs/R.md)
- [Python](/docs/R.md)
