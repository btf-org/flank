import os
from pathlib import Path
import subprocess
import urllib.request
import urllib.error
import pytest
import time


def test_serves_index(tmp_path):
    executable = "flank_server.exe" if os.name == "nt" else "flank_server"
    flank_server = Path(executable).resolve()

    index = tmp_path / "index.html"
    index.write_text("hello test")

    server = subprocess.Popen(
        [
            flank_server,
            "--port", "8084",
            "--iflank-path", "/bin/cat",
        ],
        cwd=tmp_path,
    )

    try:
        response = urllib.request.urlopen("http://localhost:8084/", timeout=2)

        assert response.status == 200
        assert response.read() == b"hello test"

    finally:
        server.terminate()
        server.wait(timeout=2)



"""
Server starts and accepts connections
Server shuts down cleanly
GET / serves index.html
Missing index.html returns 404
/_files serves an existing file
Missing /_files file returns 404
POST body reaches fake iflank
Fake iflank stdout reaches GET response
Same SID talks to same child
Different SIDs are isolated
Two sessions can operate concurrently
Long-poll GET actually waits for output
Second GET replaces/cancels previous outstanding GET
Large output works correctly
SIGTERM / equivalent shuts server down without hanging
"""
