const navHeight = $("div.navbar").height();

$(document).ready(() => {
  $(".navbar-link").on('click', (e) => {
    if(e.hash !== "") {
      event.preventDefault();
      const hash = e.target.hash;
      let scrollPosition = $(hash).offset().top - navHeight
      $('html').animate({
        scrollTop: scrollPosition
      }, 800);
    }
  });
});