
function pad(n, width, z) {
    z = z || '0';
    n = n + '';
    return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
}

function format_time(t)
{
    m = Math.floor(t / 60);
    s = t % 60;
    return (m.toString() + ":" + pad(s, 2));
}

function format_pos(pos, length)
{
    return (format_time(parseInt(pos)) + "/" + format_time(parseInt(length)));
}

function update_datas()
{
    $.getJSON("status.php", function(data) {
	fname = data.information.category[0].info;
	$("#progress-label").html("<a href='/MP3/" + encodeURIComponent(fname) + "'>" + fname + "</a>");

	pos = parseFloat(data.position).toFixed(2) * 100;
	$("#position").attr("aria-valuenow", pos);
	$("#position").attr("style", "width:" + pos.toString()  + "%");
	$("#position").text(format_pos(data.time, data.length));

	$("#volume").text(((parseInt(data.volume) * 200) / 512).toFixed(0).toString() + "%");

	if (data.state == "playing")
	    $("#playpause").text("Pause");
	else
	    $("#playpause").text("Play");
    });
}

$(function() {
    setInterval(update_datas, 1000);
});

