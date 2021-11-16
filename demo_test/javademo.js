const Nav_tongger = document.querySelector(".nav-toggler");
Nav_tongger.addEventListener("click", toggleNav);
function toggleNav(){
    document.querySelector(".nav-toggler").classList.toggle("active");
    document.querySelector(".nav").classList.toggle("open");
}
document.addEventListener("click",function(a){
    if(a.target.closest(".nav-item")){
        toggleNav();
    }
})
window.addEventListener("scroll",function(){
    // console.log(this.pageYOffset)
    if(this.pageYOffset > 60){
        document.querySelector(".header").classList.add("sticky");
    }
    else {
        document.querySelector(".header").classList.remove("sticky")
    }
})
const menuTabs = document.querySelector(".menu-taps") ;
menuTabs.addEventListener("click",function(e){
    if(e.target.classList.contains("menu-tap-item")&& !e.target.classList.contains("active"))
    {
        const target = e.target.getAttribute("data-target");
        // console.log(target);
        menuTabs.querySelector(".active").classList.remove("active");
        e.target.classList.add("active");
        const menuSection = document.querySelector(".menu-section");
        menuSection.querySelector(".menu-tap-content.active").classList.remove("active");
        menuSection.querySelector(target).classList.add("active");

     }
})
//-----------------Animation-----------
AOS.init();

  
                        