import subprocess
import time
import urllib.request


def test_serves_index():
    server = subprocess.Popen([
        "./flank_server",
        "--iflank-path", "/bin/cat",
        "--port", "8084",
    ])

    try:
        # Give flankserver a moment to start listening
        time.sleep(0.1)

        response = urllib.request.urlopen("http://localhost:8084/")
        assert response.status == 200
        body = response.read()
        # any string that is unique to index.html
        assert b"accumulatingResponse" in body

    finally:
        server.terminate()
        server.wait()
