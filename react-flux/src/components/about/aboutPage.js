"use strict";

var React = require('react');

var About = React.createClass({
	render: function(){
		return (
			<div className="container">
			<h1>About Page</h1>
			<p>This application uses:</p>
			<ul>
			<li>React</li>
			<li>React Router</li>
			<li>Flux</li>
			<li>Node</li>
			<li>Gulp</li>
			<li>Browserify</li>
			<li>Bootstrap</li>
			</ul>
			</div>
		);
	}
});

module.exports = About;
