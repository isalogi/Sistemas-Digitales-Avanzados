$(document).ready(function () {

    $("a.submenu").click(function () {
        $(".menuBar").slideToggle("normal", function () {
            // Animation complete.
        });
    });
    $("ul li.dropdown a").click(function () {
        $("ul li.dropdown ul").slideToggle("normal", function () {
            // Animation complete.
        });
        $('ul li.dropdown').toggleClass('current');
    });
});