	var svgWidth = 1800;
	var svgHeight = 1000;
	var time = 1500;
	var circleX = svgWidth/2;
	var circleY = svgHeight/2;
	var circleRad = 350;
	var svgContainer = "";
	var angles = d3.range(208).map(Math.random); 
		angles.sort(d3.ascending)
	
	var sensorCircles = [circleRad + 5, circleRad + 15, circleRad + 30, circleRad + 150];
	var origOuterPath = "";
	var origInnerPath = "";
	//setInterval(function(){createAurora();},time);
	var mindata;
	var maxdata;
	var graph1;
	var graph2;
	var graph3;
	var graph4;
	var x1;
	var x2;
	var x3;
	var x4;
	var line1;
	var line2;
	var line3;
	var line4;
	var avg1 = [];
	var avg2 = [];
	var avg3 = [];
	var avg4 = [];
	var Text1Content = "HELLO";
	var Text2Content = "We are TRAINWEAR";
	var ImageRef = "img/Smiley-Green-rating.jpg";
	Array.prototype.max = function() {
	  return Math.max.apply(null, this);
	};

	Array.prototype.min = function() {
	  return Math.min.apply(null, this);
	};
	
	function normalize(number){
		return (number - mindata)/(maxdata - mindata);
		
	}
	function createAurora(args){
		args = args.split(',');
		args.pop();
		mindata = args.min();
		maxdata = args.max();
		if(document.getElementById("aurora").innerHTML != ""){
			document.getElementById("aurora").innerHTML = "";
		}	
		var reversedArr = reverse(args);
		var sum = 0;
		for(i=0; i < args.length; i++){						
			sum = sum + parseInt(args[i]);
			if(i == 64){
				avg1.push(sum/64);
				sum = 0;
			}
			if(i == 104){
				avg2.push(sum/40);
				sum = 0;
			}
			if(i == 144){
				avg3.push(sum/40);
				sum = 0;
			}
			if(i == 207){
				avg4.push(sum/64);
				sum = 0;
			}
			
		}
		if(avg1.length > 1){
			if(avg1.length == 2){
				displayGraphExample("#graphSeries_1_1", 300, 60, "basis", true, 1000, 500, avg4, 1, '#4089f9');
				displayGraphExample("#graphSeries_1_2", 300, 60, "basis", true, 1000, 500, avg1, 2, '#ff00cc');
				displayGraphExample("#graphSeries_2_1", 300, 60, "basis", true, 1000, 500, avg3, 3, '#FCFF33');
				displayGraphExample("#graphSeries_2_2", 300, 60, "basis", true, 1000, 500, avg2, 4, '#9afe2e');
			}else{
				if(avg1.length > 50){
					avg1.shift();
					avg2.shift();
					avg3.shift();
					avg4.shift();
				}						
				redrawWithAnimation(avg4, line1, x1, graph1, '#fbae2b');
				redrawWithAnimation(avg1, line2, x2, graph2, '#ffffff');
				redrawWithAnimation(avg3, line3, x3, graph3, '#FCFF33');
				redrawWithAnimation(avg2, line4, x4, graph4, '#9afe2e');
			}
		
		}		
		//Make an SVG Container
		svgContainer = d3.select("#aurora").append("svg").attr("width", svgWidth).attr("height", svgHeight)

		//Draw the Circle		
		var data = d3.range(args.length).map(Math.random);
		//var data_outer = d3.range(80).map(Math.random);		
		
		var data_outer = [];		
		for(i=0; i < args.length; i++){
			
			data_outer.push(normalize(args[i]));
			
		}
		//var outer_angles = d3.range(80).map(Math.random); 
		//outer_angles.sort(d3.ascending)
		
		for(i=0; i < data.length; i++){
			data[i] = data[i] * (sensorCircles[1] - sensorCircles[0]) + sensorCircles[0];
			data_outer[i] = data_outer[i] * (sensorCircles[3] - sensorCircles[2]) + sensorCircles[2];
		}	
		
		var points = getOutputPoints(data, data_outer, angles, angles);						
			
		//svgContainer.datum(points.outerPlotPoints);
		var valueline = d3.svg.line()
						.interpolate("cardinal-closed");
		var outerSrcPath = valueline(points.outerPlotPoints);		
				
		var outerPath = svgContainer.append("path");
			outerPath	
			.attr("stroke", "magenta")
			.attr("stroke-width", 2)
			.attr("fill", "magenta")	
			.attr("fill-opacity", 0.40);
		
		if(origOuterPath != ""){
			outerPath
			.attr("d", origOuterPath)
			.transition()
			.duration(50)
			.attr("d", outerSrcPath)
		}else{
			outerPath
			.attr("d", outerSrcPath)			
		}	
		 origOuterPath = valueline(points.outerPlotPoints);
		//svgContainer.datum(points.plotPoints);
		//var valueline = d3.svg.line().interpolate("cardinal-closed");	
						
		var innerSrcPath = valueline(points.plotPoints);
		var innerPath = svgContainer.append("path")		
			innerPath	
			.attr("stroke", "white")
			.attr("stroke-width", 2)
			.attr("fill", "magenta")
			.attr("fill-opacity", 0.70);
			
		if(origInnerPath != ""){
			innerPath
			.attr("d", origInnerPath)
			.transition()
			.duration(50)
			.attr("d", innerSrcPath)
		}else{
			innerPath
			.attr("d", innerSrcPath)			
		}	
		origInnerPath  = valueline(points.plotPoints);			
			
		var circle = svgContainer.append("circle")
						.attr("cx", circleX)
						.attr("cy", circleY)
						.attr("r", circleRad);
		
		/* The text boxes inside the circle*/
		var rectX = circleX-60;
		var rectY = circleY-200;
		var rectWidth = 100;
		var rectHeight = 100;
		var textWidth = 200;
		var textHeight = 50;
		
		var textX = circleX ;//- (textWidth/2);
		var textY = circleY - (circleY/3);
		
		/*var rect = svgContainer.append("rect")
					.attr("x", rectX)
					.attr("y", rectY)
					.attr("width", rectWidth)
					.attr("height", rectHeight)
					.attr("fill", "yellow")
					.attr("fill-opacity", 0.5);		*/		
		var textContainer = svgContainer.append("text")
			.attr("dx", textX)
			.attr("dy", textY)
			.text(Text1Content)  //string 
			.attr('text-anchor', 'middle')
			.attr("font-family", "sans-serif")
			.attr("font-size", "40px")
			.attr("fill", "white");	
		textY = circleY + (circleY/3);	
		/*var rect = svgContainer.append("rect")
					.attr("x", rectX)
					.attr("y", rectY)
					.attr("width", rectWidth)
					.attr("height", rectHeight)
					.attr("fill", "yellow")
					.attr("fill-opacity", 0.5);	*/			
		var textContainer = svgContainer.append("text")
					.attr("dx", textX)
					.attr("dy", textY)
					.attr('style', 'text-align: center')
					.text(Text2Content)
					.attr('text-anchor', 'middle')
					.attr("font-size", "40px")
					.attr("fill", "white");	
		rectX = circleX-rectWidth/2;
		rectY = circleY-rectHeight/2;
		
		var rect=svgContainer.append("svg:image")
				.attr("xlink:href",ImageRef)
				.attr("x",rectX)
				.attr("y",rectY)
				.attr("width",rectWidth)
				.attr("height",rectHeight)
				
		var rect=svgContainer.append("svg:image")
				.attr("xlink:href","img/logo_b.jpg")
				.attr("x",100)
				.attr("y",rectY)
				.attr("width",250)
				.attr("height",100)
					
		/* The text boxes inside the circle*/			
					
		/* var defs = svgContainer.append("defs")		
		var rect = svgContainer.append("rect")
					.attr("x", circleX-500)
					.attr("y", circleY-200)
					.attr("width", 200)
					.attr("height", 100)
					.attr("fill", "yellow")
					.attr("fill-opacity", 0.5);
		defs.append("marker")
				.attr({
					"id":"arrow",
					"viewBox":"0 -5 10 10",
					"refX":5,
					"refY":0,
					"markerWidth":4,
					"markerHeight":4,
					"orient":"auto",
					"fill":"magenta"
				})
				.append("path")
					.attr("d", "M0,-5L10,0L0,5")
					.attr("class","arrowHead");			
					
		var p1 = (circleX-300) ;
		var p2 = circleY-100;
		var p3 = (circleX-240) ;
		var p4 = circleY-70;
		svgContainer.append("line")          
			.style("stroke", "magenta")  
			.attr("x1", p1)     
			.attr("y1", p2)     
			.attr("x2", p3)     
			.attr("y2", p4)
			.style("stroke-dasharray", ("3, 3"))
			.attr("stroke-width", 2)
			.attr("marker-end", "url(#arrow)"); 
		var rect = svgContainer.append("rect")
					.attr("x", circleX-500)
					.attr("y", circleY+200)
					.attr("width", 200)
					.attr("height", 100)
					.attr("fill", "yellow")
					.attr("fill-opacity", 0.5);
		
		var p1 = (circleX-300) ;
		var p2 = circleY+200;
		var p3 = (circleX-240) ;
		var p4 = circleY+170;
		svgContainer.append("line")          
			.style("stroke", "magenta")  
			.attr("x1", p1)     
			.attr("y1", p2)      
			.attr("x2", p3)    
			.attr("y2", p4)
			.style("stroke-dasharray", ("3, 3"))
			.attr("stroke-width", 2)
			.attr("marker-end", "url(#arrow)"); 
		
		var rect = svgContainer.append("rect")
					.attr("x", circleX+300)
					.attr("y", circleY-200)
					.attr("width", 200)
					.attr("height", 100)
					.attr("fill", "yellow")
					.attr("fill-opacity", 0.5);
					
		var p1 = (circleX+300) ;
		var p2 = circleY-100;
		var p3 = (circleX+240) ;
		var p4 = circleY-70;
		svgContainer.append("line")          
			.style("stroke", "magenta")  
			.attr("x1", p1)     
			.attr("y1", p2)      
			.attr("x2", p3)    
			.attr("y2", p4)
			.style("stroke-dasharray", ("3, 3"))
			.attr("stroke-width", 2)
			.attr("marker-end", "url(#arrow)");			

		var rect = svgContainer.append("rect")
					.attr("x", circleX+300)
					.attr("y", circleY+200)
					.attr("width", 200)
					.attr("height", 100)
					.attr("fill", "yellow")
					.attr("fill-opacity", 0.5);		

		var p1 = (circleX+300) ;
		var p2 = circleY+200;
		var p3 = (circleX+240) ;
		var p4 = circleY+170;
		svgContainer.append("line")          
			.style("stroke", "magenta")  
			.attr("x1", p1)     
			.attr("y1", p2)      
			.attr("x2", p3)    
			.attr("y2", p4)
			.style("stroke-dasharray", ("3, 3"))
			.attr("stroke-width", 2)
			.attr("marker-end", "url(#arrow)");	 */			
	}

	function transition(path) {
	  path.transition()
		  .duration(500)
		  .attrTween("stroke-dasharray", tweenDash)
		  .each("end", function() { d3.select(this).call(transition); });
	}	
	function tweenDash() {
	  var l = this.getTotalLength(),
		  i = d3.interpolateString("0," + l, l + "," + l);
	  return function(t) { 
	  
			//console.log(t);
			//console.log(i(t));	
			return i(t); 
	  
	  };
	}
	
	function getOutputPoints(data, data_outer, angles, outer_angles){
		var points = {}
		var plotPoints = [];
		var outerPlotPoints = [];
		for(i=0; i < data.length; i++){
			var pointX = circleX + ((data[i]) * Math.sin(2*Math.PI*angles[i]));
			var pointY = circleY - ((data[i]) * Math.cos(2*Math.PI*angles[i]))
			var outerPointX = circleX + ((data_outer[i]) * Math.sin(2*Math.PI*outer_angles[i]));
			var outerPointY = circleY - ((data_outer[i]) * Math.cos(2*Math.PI*outer_angles[i]))
			plotPoints.push([pointX, pointY]);
			outerPlotPoints.push([outerPointX, outerPointY]);
			svgContainer.append("circle").attr("cx", pointX)
					.attr("cy", pointY)
					.attr("r", 1);
			svgContainer.append("circle").attr("cx", outerPointX)
					.attr("cy", outerPointY)
					.attr("r", 1);
		}
		points.plotPoints = plotPoints;
		points.outerPlotPoints = outerPlotPoints;
		return points;
	}
	function displayGraphExample(id, width, height, interpolation, animate, updateDelay, transitionDelay, data, idnum, color) {
		var x;
		var line;
		var graph;	
		// create an SVG element inside the #graph div that fills 100% of the div
		graph = d3.select(id).append("svg:svg").attr("width", "100%").attr("height", "100%");

		// create a simple data array that we'll plot with a line (this array represents only the Y values, X will just be the index location)
		//var data = [3, 6, 2, 7, 5, 2, 1, 3, 8, 9, 2, 5, 9, 3, 6, 3, 6, 2, 7, 5, 2, 1, 3, 8, 9, 2, 5, 9, 2, 7, 5, 2, 1, 3, 8, 9, 2, 5, 9, 3, 6, 2, 7, 5, 2, 1, 3, 8, 9, 2, 9];

		// X scale will fit values from 0-10 within pixels 0-100
		x = d3.scale.linear().domain([0, 48]).range([-10, width]); // starting point is -5 so the first value doesn't show and slides off the edge as part of the transition
		// Y scale will fit values from 0-10 within pixels 0-100
		var y = d3.scale.linear().domain([0, 10]).range([0, height]);

		// create a line object that represents the SVN line we're creating
		line = d3.svg.line()
			// assign the X function to plot our line as we wish
			.x(function(d,i) { 
				// verbose logging to show what's actually being done
				//console.log('Plotting X value for data point: ' + d + ' using index: ' + i + ' to be at: ' + x(i) + ' using our xScale.');
				// return the X coordinate where we want to plot this datapoint
				return x(i); 
			})
			.y(function(d) { 
				// verbose logging to show what's actually being done
				//console.log('Plotting Y value for data point: ' + d + ' to be at: ' + y(d) + " using our yScale.");
				// return the Y coordinate where we want to plot this datapoint
				return y(d); 
			})
			.interpolate(interpolation)

			// display the line by appending an svg:path element with the data line we created above
			graph.append("svg:path").attr("d", line(data));
			// or it can be done like this
			//graph.selectAll("path").data([data]).enter().append("svg:path").attr("d", line);
			if(idnum ==1){
				graph1 = graph;
				x1 = x;
				line1 = line;		
			}else if(idnum ==2){
				graph2 = graph;
				x2 = x;
				line2 = line;			
			}else if(idnum ==3){
				graph3 = graph;
				x3 = x;
				line3 = line;			
			}else if(idnum ==4){
				graph4 = graph;
				x4 = x;
				line4 = line;			
			}			
			redrawWithAnimation(data, line,x, graph, color);		
		}
	function redrawWithAnimation(dataArr,line,x, graph,color) {
		//console.log(dataArr);
		// update with animation
		graph.selectAll("path")
			.data([dataArr]) // set the new data
			.attr("stroke", color)
			.attr("stroke-width", 8)
			.style("fill", "#444444")
			.attr("transform", "translate(" + x(1) + ")") // set the transform to the right by x(1) pixels (6 for the scale we've set) to hide the new value
			.attr("d", line) // apply the new data values ... but the new value is hidden at this point off the right of the canvas
			.transition() // start a transition to bring the new value into view
			.ease("linear")
			.duration(time) // for this demo we want a continual slide so set this to the same as the setInterval amount below
			.attr("transform", "translate(" + x(0) + ")"); // animate a slide to the left back to x(0) pixels to reveal the new value
			
			/* thanks to 'barrym' for examples of transform: https://gist.github.com/1137131 */
	}
	
	function reverse(arr){
		var sliced1 = arr.slice(0,arr.length/2);
		var sliced2 = arr.slice(arr.length/2,arr.length);
		var sliced2_1 = arr.slice(arr.length/2,arr.length/2+64);
		var sliced2_2 = arr.slice(arr.length/2+64,arr.length);
		var concatArr = sliced1.concat(sliced2_2);
		concatArr = concatArr.concat(sliced2_1);
		return concatArr;		
	}
	function writeText1(textIn){
		Text1Content = textIn;
	}
	function writeText2(textIn){
		Text2Content = textIn;
	}
	function changeImage1(imgLink){
		ImageRef = imgLink;
	}