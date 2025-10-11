
PAGE='HOME'
PROMPT='iflank> '

cd /opt/homebrew/var/flank
while true; do
    case "$PAGE" in
	HOME)
	    echo 'Welcome to Flank!'
	    echo ''
	    echo '(C)ommands / (P)rocesses'
	    echo ''
	    read -rp "$PROMPT" choice
	    case $choice in
		C)
		    PAGE='FS'
		    ;;
		P)
		    PAGE='PS'
		    ;;
		*)
		    read -rp "Invalid choice! Hit [Enter] to continue"
		    ;;
	    esac
	    ;;
	PS)
	    ps
	    echo ''
	    echo '(B)ack / (K)ill <pid>'
	    echo ''
	    read -rp "$PROMPT" choice args
	    case $choice in 
		B)
		    PAGE='HOME'
		    ;;
		K)
		    kill $args 
		    PAGE='PS'
		    ;;
		*)
		    read -rp "Invalid choice! Hit [Enter] to continue"
		    ;;
	    esac
	    ;;
	FS)
	    pwd
	    echo ""
	    ls -1
	    echo ""
	    echo "Next: (G)oto <name>"
	    echo ""
	    read -rp "$PROMPT" choice arg
	    case $choice in
		G)
		    cd $arg
		    if [ -f blackbox.sh ]; then
			PAGE='CMD'
		    else
			PAGE='FS'
		    fi
		    ;;
		*)
		    read -rp "Invalid choice! Hit [Enter] to continue"
		    ;;
	    esac
	    ;;
	CMD)
	    pwd
	    echo ''
	    echo 'Next: (R)un / (H)ome'
	    echo ''
	    read -rp "$PROMPT" choice
	    case $choice in
		R)
		    bash blackbox.sh
		    PAGE='CMD'
		    ;;
		H)
		    PAGE='HOME'
		    ;;
		*)
		    read -rp "Invalid choice! Hit [Enter] to continue"
		    ;;
	    esac
	    ;;
	*)
	    echo "Got into weird state. Hit Ctrl-C to quit"
	    ;;
    esac
done
