#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netdevice.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suchakra Sharma");
MODULE_DESCRIPTION("Simple packet filter");

static struct nf_hook_ops hops;

unsigned int filter_hook(unsigned int hooknum, struct sk_buff *skb,
        const struct net_device *in, const struct net_device *out,
        int (*okfn)(struct sk_buff *))  
{
    if (!strcmp(in->name, "lo") && skb->protocol == 8)
    {
        printk(KERN_INFO "PACKET FILTER: Mumbai local\n");
        return NF_ACCEPT;
    }
    return NF_ACCEPT;
}

static int init_filter(void)
{
    hops.hook = (nf_hookfn*) filter_hook;
    hops.hooknum = NF_INET_PRE_ROUTING; //NF_IP_PRE_ROUTING
    hops.pf = PF_INET;
    hops.priority = NF_IP_PRI_FIRST;
    nf_register_hook(&hops);
    return 0;
}

static int __init packetfilter_init(void)
{
    printk(KERN_INFO "PACKET FILTER: Initializing..\n");
    init_filter();
    return 0;
}

static void __exit packetfilter_cleanup(void)
{
    nf_unregister_hook(&hops);
    printk(KERN_INFO "PACKET FILTER: Cleanup\n");
}

module_init(packetfilter_init);
module_exit(packetfilter_cleanup);
