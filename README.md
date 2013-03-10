<h1>Benchling Backend Coding Challenge Writeup:</h1>
<h2>Major Design Choices and Why I Chose Them:</h2>
<p><b>Ruby On Rails:</b> Rails is a quick and powerful way to build web apps</p>
<p><b>Thin Server:</b> The Thin Ruby web server is a quality server which incorporates The Mongrel Parser, Eventmachine and Rack.</p>
<p><b>Fibers:</b> Ruby Fibers allow you to write asynchronous code (which is typically very complicated to read because it uses callbacks instead of linear coding) in what appears to be linear code.  This enables much more readable code.<p>
<p><b>EM-Synchrony:</b> Provides Eventmachine compatible code for many common rails applications.<p>
<p><b>EM-PostgreSQL:</b> Provides a postgres driver that operates asynchronously, allowing you to use Rails ActiveRecord models the way you normally would but operating asynchronously under the hood.<p>
<p><b>Protobuf:</b> Provides an efficient and standardized method of encoding data to be transferred between the device and the server. Chosen over other encoding protocols for it's support in both the Rails and Arduino environments.</p>
<p><b>EM-Amazon S3:</b> Because you mentioned that binary data such as unprocessed images may be uploaded, I decided to store this data in a .proto file stored in an S3 bucket as opposed to a binary field in the database.  This is because most databases have size limits on what can be stored in a field while S3 does not.  This allows the application to be significantly more scalable.  The EM library sends all the S3 requests using eventmachine under the hood so as to remove any blocking I/O.<p>
<p><b>Paperclip:</b> The Paperclip gem enables you to manage files stored on S3 as if they were an attribute of an ActiveRecord Model.  This provides for much simpler and more readable code.<p>

<h2>How to set up:</h2>
<ol>
  <li>Go to the root directory and click "Register A New Device"</li>
  <li>Take note of both your device id and registration key.  The device id will be how you view messages sent from the device and the registration key will be required to authenticate messages from your device.</li>
</ol>
