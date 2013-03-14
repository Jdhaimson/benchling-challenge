<h1>Benchling Backend Coding Challenge:</h1>

<h2>Major Design Choices:</h2>
<p><b>Thin Server:</b> The Thin Ruby web server is a quality server which incorporates The Mongrel Parser, Eventmachine and Rack.</p>
<p><b>Fibers:</b> Ruby Fibers allow you to write asynchronous code (which is typically very complicated to read because it uses callbacks instead of linear coding) in what appears to be linear code.  This enables much more readable code.<p>
<p><b>EM-Synchrony:</b> Provides Eventmachine compatible code for many common rails applications.<p>
<p><b>EM-PostgreSQL:</b> Provides a postgres driver that operates asynchronously, allowing you to use Rails ActiveRecord models the way you normally would but operating asynchronously under the hood.<p>
<p><b>Protobuf:</b> Provides an efficient and standardized method of encoding data to be transferred between the device and the server. Chosen over other encoding protocols for it's support in both the Rails and Arduino environments.</p>

<h2>How to set up:</h2>
<ol>
  <li>Go to the root directory and click "Register A New Device"</li>
  <li>Take note of both your device id and registration key.  The device id will be how you view messages sent from the device and the registration key will be required to authenticate messages from your device.</li>
  </li>Enter that information at the top of the examples/arduino/device/device.ino arduino code</li>
</ol>

<h2>Performance</h2>
<p>Without eventmachine, the server could not handle more than 35 concurrent requests without having to reset the connection.  With eventmachine, the server was able to handle at least 200 concurrent requests without reseting the connection, and processed them at 47.46 requests/second.</p>
<h3>With EM, 200 concurrent requests</h3>
    ab -c 200 -n 1000 http://127.0.0.1:3000/devices/14/messages
    This is ApacheBench, Version 2.3 <$Revision: 655654 $>
    Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
    Licensed to The Apache Software Foundation, http://www.apache.org/

    Server Software:        thin
    Server Hostname:        127.0.0.1
    Server Port:            3000

    Document Path:          /devices/14/messages
    Document Length:        1310 bytes

    Concurrency Level:      200
    Time taken for tests:   21.072 seconds
    Complete requests:      1000
    Failed requests:        0
    Write errors:           0
    Total transferred:      1857000 bytes
    HTML transferred:       1310000 bytes
    Requests per second:    47.46 [#/sec] (mean)
    Time per request:       4214.422 [ms] (mean)
    Time per request:       21.072 [ms] (mean, across all concurrent requests)
    Transfer rate:          86.06 [Kbytes/sec] received

    Connection Times (ms)
                  min  mean[+/-sd] median   max
    Connect:        0    2   3.3      0      10
    Processing:   822 3832 839.3   4181    4368
    Waiting:      413 3809 855.4   4163    4355
    Total:        831 3834 836.6   4181    4375

    Percentage of the requests served within a certain time (ms)
      50%   4181
      66%   4209
      75%   4221
      80%   4229
      90%   4238
      95%   4246
      98%   4267
      99%   4273
     100%   4375 (longest request)

<h3>No EM, 200 concurrent requests</h3>
    ab -c 200 -n 1000 http://127.0.0.1:3000/devices/14/messages
    This is ApacheBench, Version 2.3 <$Revision: 655654 $>
    Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
    Licensed to The Apache Software Foundation, http://www.apache.org/

    Benchmarking 127.0.0.1 (be patient)
    Completed 100 requests
    apr_socket_recv: Connection reset by peer (104)
    Total of 152 requests completed

<h3>No EM, 40 concurrent requests</h3>
    ab -c 40 -n 1000 http://127.0.0.1:3000/devices/14/messages
    This is ApacheBench, Version 2.3 <$Revision: 655654 $>
    Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
    Licensed to The Apache Software Foundation, http://www.apache.org/

    Benchmarking 127.0.0.1 (be patient)
    Completed 100 requests
    Completed 200 requests
    apr_socket_recv: Connection reset by peer (104)
    Total of 239 requests completed

<h3>No EM, 35 concurrent requests</h3>
    ab -c 35 -n 1000 http://127.0.0.1:3000/devices/14/messages
    This is ApacheBench, Version 2.3 <$Revision: 655654 $>
    Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
    Licensed to The Apache Software Foundation, http://www.apache.org/

    Server Software:        WEBrick/1.3.1
    Server Hostname:        127.0.0.1
    Server Port:            3000

    Document Path:          /devices/14/messages
    Document Length:        1310 bytes

    Concurrency Level:      35
    Time taken for tests:   28.071 seconds
    Complete requests:      1000
    Failed requests:        0
    Write errors:           0
    Total transferred:      1998000 bytes
    HTML transferred:       1310000 bytes
    Requests per second:    35.62 [#/sec] (mean)
    Time per request:       982.471 [ms] (mean)
    Time per request:       28.071 [ms] (mean, across all concurrent requests)
    Transfer rate:          69.51 [Kbytes/sec] received

    Connection Times (ms)
                  min  mean[+/-sd] median   max
    Connect:        0    7  83.3      0    1000
    Processing:    25  961 140.9    972    1970
    Waiting:       23  958 141.0    969    1970
    Total:         25  968 161.1    972    2198

    Percentage of the requests served within a certain time (ms)
      50%    972
      66%    992
      75%   1009
      80%   1019
      90%   1045
      95%   1065
      98%   1099
      99%   1855
     100%   2198 (longest request)
