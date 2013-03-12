<h1>Benchling Backend Coding Challenge Writeup:</h1>
<h2>Major Design Choices and Why I Chose Them:</h2>
<p><b>Ruby On Rails:</b> Rails is a quick and powerful way to build web apps</p>
<p><b>Thin Server:</b> The Thin Ruby web server is a quality server which incorporates The Mongrel Parser, Eventmachine and Rack.</p>
<p><b>Fibers:</b> Ruby Fibers allow you to write asynchronous code (which is typically very complicated to read because it uses callbacks instead of linear coding) in what appears to be linear code.  This enables much more readable code.<p>
<p><b>EM-Synchrony:</b> Provides Eventmachine compatible code for many common rails applications.<p>
<p><b>EM-PostgreSQL:</b> Provides a postgres driver that operates asynchronously, allowing you to use Rails ActiveRecord models the way you normally would but operating asynchronously under the hood.<p>
<p><b>Protobuf:</b> Provides an efficient and standardized method of encoding data to be transferred between the device and the server. Chosen over other encoding protocols for it's support in both the Rails and Arduino environments.</p>

<h2>How to set up:</h2>
<ol>
  <li>Go to the root directory and click "Register A New Device"</li>
  <li>Take note of both your device id and registration key.  The device id will be how you view messages sent from the device and the registration key will be required to authenticate messages from your device.</li>
</ol>
